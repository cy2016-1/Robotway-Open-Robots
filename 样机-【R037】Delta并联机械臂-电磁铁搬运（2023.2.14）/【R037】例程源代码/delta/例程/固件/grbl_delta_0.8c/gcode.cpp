/*
 * refactor
 * 2018/12/23
 */
#include <Arduino.h>
#include "gcode.h"
#include <string.h>
#include "nuts_bolts.h"
#include <math.h>
#include "settings.h"
#include "motion_control.h"
#include "spindle_control.h"
#include "spindle_control.h"
#include "coolant_control.h"
#include "errno.h"
#include "protocol.h"
#include "report.h"
#include "user_settings.h"
#include "delta_config.h"
#include "print.h"

parser_state_t gc;

#define FAIL(status) gc.status_code = status;

static int next_statement(char *letter, float *float_ptr, char *line, uint8_t *char_counter);

static void select_plane(uint8_t axis_0, uint8_t axis_1, uint8_t axis_2) 
{
  gc.plane_axis_0 = axis_0;
  gc.plane_axis_1 = axis_1;
  gc.plane_axis_2 = axis_2;
}

void gc_init() 
{
  memset(&gc, 0, sizeof(gc));
  gc.feed_rate = settings.default_feed_rate; 
//  gc.seek_rate = settings.default_seek_rate;
  select_plane(X_AXIS, Y_AXIS, Z_AXIS);
  gc.absolute_mode = true;
  
  // Load default G54 coordinate system.
  if (!(settings_read_coord_data(gc.coord_select,gc.coord_system))) { 
    report_status_message(STATUS_SETTING_READ_FAIL); 
  } 
}

void gc_set_current_position(int32_t x, int32_t y, int32_t z) 
{
  gc.position[X_AXIS] = x/settings.steps_per_mm[X_AXIS];
  gc.position[Y_AXIS] = y/settings.steps_per_mm[Y_AXIS];
  gc.position[Z_AXIS] = z/settings.steps_per_mm[Z_AXIS]; 
}

static float to_millimeters(float value) 
{
  return(gc.inches_mode ? (value * MM_PER_INCH) : value);
}

uint8_t gc_execute_line(char * line)
{
  if(sys.state == STATE_ALARM) { return (STATUS_ALARM_LOCK); }

  uint8_t char_counter = 0;
  char letter;
  float value;
  int int_value;

  uint16_t modal_group_words = 0;
  uint8_t axis_words = 0;

  float inverse_feed_rate = -1;
  uint8_t absolute_override = false;
  uint8_t non_modal_action = NON_MODAL_NONE; 
  
  float target[3], offset[3];
  clear_vector(target); 
  clear_vector(offset);

  gc.status_code = STATUS_OK;

  //pass 1
  uint8_t group_number = MODAL_GROUP_NONE;
  while(next_statement(&letter, &value, line, &char_counter))
  {
    int_value = trunc(value);
    switch(letter)
    {
      case 'G':
        //set modal group values
        switch(int_value) 
        {
          case 4: case 10: case 28: case 30: case 53: case 92: group_number = MODAL_GROUP_0; break;
          case 0: case 1: case 2: case 3: case 80: group_number = MODAL_GROUP_1; break;
          case 17: case 18: case 19: group_number = MODAL_GROUP_2; break;
          case 90: case 91: group_number = MODAL_GROUP_3; break;
          case 93: case 94: group_number = MODAL_GROUP_5; break;
          case 20: case 21: group_number = MODAL_GROUP_6; break;
          case 54: case 55: case 56: case 57: case 58: case 59: group_number = MODAL_GROUP_12; break;
        }    
        //set 'G' commands
        switch(int_value)
        {
          case 0: gc.motion_mode = MOTION_MODE_SEEK; bit_true(axis_words,bit(Z_AXIS)); break;
          case 1: gc.motion_mode = MOTION_MODE_LINEAR; bit_true(axis_words,bit(Z_AXIS)); break;
          case 20: gc.inches_mode = true; break;
          case 21: gc.inches_mode = false; break;
          case 90: gc.absolute_mode = true; break;
          case 91: gc.absolute_mode = false; break;
          case 92: 
            int_value = trunc(10*value); // Multiply by 10 to pick up G92.1
            switch(int_value) {
              case 920: non_modal_action = NON_MODAL_SET_COORDINATE_OFFSET; break;        
              case 921: non_modal_action = NON_MODAL_RESET_COORDINATE_OFFSET; break;
              default: FAIL(STATUS_UNSUPPORTED_STATEMENT);
            }
            break;
          case 93: gc.inverse_feed_rate_mode = true; break;
          case 94: gc.inverse_feed_rate_mode = false; break;
          default: FAIL(STATUS_UNSUPPORTED_STATEMENT);
        }
        break;
      case 'M':
        //set modal group values
        switch(int_value) 
        {
          case 0: case 1: case 2: case 30: group_number = MODAL_GROUP_4; break;
          case 3: case 4: case 5: group_number = MODAL_GROUP_7; break;
        } 
        //set 'M' commands
        switch(int_value)
        {
          case 0: gc.program_flow = PROGRAM_FLOW_PAUSED; break; // Program pause
          case 1: break; // Optional stop not supported. Ignore.
          case 2: case 30: gc.program_flow = PROGRAM_FLOW_COMPLETED; break; // Program end and reset 
          case 3: 
            gc.spindle_direction = 1; 
            break;
          case 4: gc.spindle_direction = -1; break;
          case 5: 
            gc.spindle_direction = 0;        
            break;
          #ifdef ENABLE_M7
            case 7: gc.coolant_mode = COOLANT_MIST_ENABLE; break;
          #endif
          case 8: gc.coolant_mode = COOLANT_FLOOD_ENABLE; break;
          case 9: gc.coolant_mode = COOLANT_DISABLE; break;
          default: FAIL(STATUS_UNSUPPORTED_STATEMENT);
        }
        break;
    }
    // Check for modal group multiple command violations in the current block
    if (group_number) 
    {
      if ( bit_istrue(modal_group_words,bit(group_number)) ) {
        FAIL(STATUS_MODAL_GROUP_VIOLATION);
      } else {
        bit_true(modal_group_words,bit(group_number));
      }
      group_number = MODAL_GROUP_NONE; // Reset for next command.
    } 
  }

  if (gc.status_code) { return(gc.status_code); }

  //pass 2
  float p = 0;
  uint8_t l = 0;
  char_counter = 0;
  while(next_statement(&letter, &value, line, &char_counter))
  {
    switch(letter)
    {
      case 'G': case 'M': case 'N': break;
      case 'F': 
        if (value <= 0) { FAIL(STATUS_INVALID_STATEMENT); } // Must be greater than zero
        if (gc.inverse_feed_rate_mode) {
          inverse_feed_rate = to_millimeters(value); // seconds per motion for this motion only
        } else {          
          gc.feed_rate = to_millimeters(value); // millimeters per minute
        }
        break;
      case 'S':
        if (value < 0) { FAIL(STATUS_INVALID_STATEMENT); } // Cannot be negative
        //gc.spindle_direction = 1;      
        break;
      case 'T':
        if (value < 0) { FAIL(STATUS_INVALID_STATEMENT); } // Cannot be negative
        gc.tool = trunc(value); 
        break;
      case 'X': target[X_AXIS] = to_millimeters(value); bit_true(axis_words,bit(X_AXIS)); break;  //世界坐标系x所走距离
      case 'Y': target[Y_AXIS] = to_millimeters(value); bit_true(axis_words,bit(Y_AXIS)); break;  //世界坐标系y所走距离
      case 'Z': target[Z_AXIS] = value; bit_true(axis_words,bit(Z_AXIS)); break;                  //车自身所转动角度
      default: FAIL(STATUS_UNSUPPORTED_STATEMENT); 
    }  
  }
  
  //calculate the distance of three axis
  float t_x = target[X_AXIS];
  float t_y = target[Y_AXIS];
  float t_z = target[Z_AXIS];
  
  target[X_AXIS] = sqrt(delta_diagonal_rod_2
                        - sq(delta_tower1_x - t_x)
                        - sq(delta_tower1_y - t_y)
                       ) + t_z - delta_axis_none;
  target[Y_AXIS] = sqrt(delta_diagonal_rod_2
                        - sq(delta_tower2_x - t_x)
                        - sq(delta_tower2_y - t_y) 
                       ) + t_z - delta_axis_none;
  target[Z_AXIS] = sqrt(delta_diagonal_rod_2
                        - sq(delta_tower3_x - t_x)
                        - sq(delta_tower3_y - t_y)
                       ) + t_z - delta_axis_none;

  /*
  printFloat(target[X_AXIS]);
  printString("\n");
  printFloat(target[Y_AXIS]);
  printString("\n");
  printFloat(target[Z_AXIS]);
  printString("\n");
  */

  if (gc.status_code) { return(gc.status_code); }

  if (sys.state != STATE_CHECK_MODE) { 
    //  ([M6]: Tool change should be executed here.)

    // [M3,M4,M5]: Update spindle state
    spindle_run(gc.spindle_direction);
  
    // [*M7,M8,M9]: Update coolant state
    coolant_run(gc.coolant_mode);
  }

  if ( bit_istrue(modal_group_words,bit(MODAL_GROUP_12)) ) { // Check if called in block
    float coord_data[N_AXIS];
    if (!(settings_read_coord_data(gc.coord_select,coord_data))) { return(STATUS_SETTING_READ_FAIL); } 
    memcpy(gc.coord_system,coord_data,sizeof(coord_data));
  }

uint8_t home_select;
  switch (non_modal_action) {
    case NON_MODAL_DWELL:
      if (p < 0) { // Time cannot be negative.
        FAIL(STATUS_INVALID_STATEMENT); 
      } else {
        // Ignore dwell in check gcode modes
        if (sys.state != STATE_CHECK_MODE) { mc_dwell(p); }
      }
      break;
    case NON_MODAL_SET_COORDINATE_DATA:
      int_value = trunc(p); // Convert p value to int.
      if ((l != 2 && l != 20) || (int_value < 1 || int_value > N_COORDINATE_SYSTEM)) { // L2 and L20. P1=G54, P2=G55, ... 
        FAIL(STATUS_UNSUPPORTED_STATEMENT); 
      } else if (!axis_words && l==2) { // No axis words.
        FAIL(STATUS_INVALID_STATEMENT);
      } else {
        int_value--; // Adjust P index to EEPROM coordinate data indexing.
        if (l == 20) {
          settings_write_coord_data(int_value,gc.position);
          // Update system coordinate system if currently active.
          if (gc.coord_select == int_value) { memcpy(gc.coord_system,gc.position,sizeof(gc.position)); }
        } else {
          float coord_data[N_AXIS];
          if (!settings_read_coord_data(int_value,coord_data)) { return(STATUS_SETTING_READ_FAIL); }
          // Update axes defined only in block. Always in machine coordinates. Can change non-active system.
          uint8_t i;
          for (i=0; i<N_AXIS; i++) { // Axes indices are consistent, so loop may be used.
            if ( bit_istrue(axis_words,bit(i)) ) { coord_data[i] = target[i]; }
          }
          settings_write_coord_data(int_value,coord_data);
          // Update system coordinate system if currently active.
          if (gc.coord_select == int_value) { memcpy(gc.coord_system,coord_data,sizeof(coord_data)); }
        }
      }
      axis_words = 0; // Axis words used. Lock out from motion modes by clearing flags.
      break;
    case NON_MODAL_GO_HOME_0: case NON_MODAL_GO_HOME_1: 
      // Move to intermediate position before going home. Obeys current coordinate system and offsets 
      // and absolute and incremental modes.
      if (axis_words) {
        // Apply absolute mode coordinate offsets or incremental mode offsets.
        uint8_t i;
        for (i=0; i<N_AXIS; i++) { // Axes indices are consistent, so loop may be used.
          if ( bit_istrue(axis_words,bit(i)) ) {
            if (gc.absolute_mode) {
              target[i] += gc.coord_system[i] + gc.coord_offset[i];
            } else {
              target[i] += gc.position[i];
            }
          } else {
            target[i] = gc.position[i];
          }
        }
        mc_line(target[X_AXIS], target[Y_AXIS], target[Z_AXIS], settings.default_seek_rate, false);
      }
      // Retreive G28/30 go-home position data (in machine coordinates) from EEPROM
      float coord_data[N_AXIS];
      home_select = SETTING_INDEX_G28;
      if (non_modal_action == NON_MODAL_GO_HOME_1) { home_select = SETTING_INDEX_G30; }
      if (!settings_read_coord_data(home_select,coord_data)) { return(STATUS_SETTING_READ_FAIL); }
      mc_line(coord_data[X_AXIS], coord_data[Y_AXIS], coord_data[Z_AXIS], settings.default_seek_rate, false); 
      memcpy(gc.position, coord_data, sizeof(coord_data)); // gc.position[] = coord_data[];
      axis_words = 0; // Axis words used. Lock out from motion modes by clearing flags.
      break;
    case NON_MODAL_SET_HOME_0: case NON_MODAL_SET_HOME_1:
      home_select = SETTING_INDEX_G28;
      if (non_modal_action == NON_MODAL_SET_HOME_1) { home_select = SETTING_INDEX_G30; }
      settings_write_coord_data(home_select,gc.position);
      break;
    case NON_MODAL_SET_COORDINATE_OFFSET:
      if (!axis_words) { // No axis words
        FAIL(STATUS_INVALID_STATEMENT);
      } else {
        // Update axes defined only in block. Offsets current system to defined value. Does not update when
        // active coordinate system is selected, but is still active unless G92.1 disables it. 
        uint8_t i;
        for (i=0; i<=2; i++) { // Axes indices are consistent, so loop may be used.
          if (bit_istrue(axis_words,bit(i)) ) {
            gc.coord_offset[i] = gc.position[i]-gc.coord_system[i]-target[i];
          }
        }
      }
      axis_words = 0; // Axis words used. Lock out from motion modes by clearing flags.
      break;
    case NON_MODAL_RESET_COORDINATE_OFFSET: 
      clear_vector(gc.coord_offset); // Disable G92 offsets by zeroing offset vector.
      break;
  }

  if ( bit_istrue(modal_group_words,bit(MODAL_GROUP_1)) || axis_words ) {

    // G1,G2,G3 require F word in inverse time mode.  
    if ( gc.inverse_feed_rate_mode ) { 
      if (inverse_feed_rate < 0 && gc.motion_mode != MOTION_MODE_CANCEL) {
        FAIL(STATUS_INVALID_STATEMENT);
      }
    }
    // Absolute override G53 only valid with G0 and G1 active.
    if ( absolute_override && !(gc.motion_mode == MOTION_MODE_SEEK || gc.motion_mode == MOTION_MODE_LINEAR)) {
      FAIL(STATUS_INVALID_STATEMENT);
    }
    // Report any errors.  
    if (gc.status_code) { return(gc.status_code); }

    // Convert all target position data to machine coordinates for executing motion. Apply
    // absolute mode coordinate offsets or incremental mode offsets.
    // NOTE: Tool offsets may be appended to these conversions when/if this feature is added.
    uint8_t i;
    for (i=0; i<=2; i++) { // Axes indices are consistent, so loop may be used to save flash space.
      if ( bit_istrue(axis_words,bit(i)) ) {
        if (!absolute_override) { // Do not update target in absolute override mode
          if (gc.absolute_mode) {
            target[i] += gc.coord_system[i] + gc.coord_offset[i]; // Absolute mode
          } else {
            target[i] += gc.position[i]; // Incremental mode
          }
        }
      } else {
        target[i] = gc.position[i]; // No axis word in block. Keep same axis position.
      }
    }
  
    switch (gc.motion_mode) {
      case MOTION_MODE_CANCEL: 
        if (axis_words) { FAIL(STATUS_INVALID_STATEMENT); } // No axis words allowed while active.
        break;
      case MOTION_MODE_SEEK:
        if (!axis_words) { FAIL(STATUS_INVALID_STATEMENT);} 
        else { mc_line(target[X_AXIS], target[Y_AXIS], target[Z_AXIS], settings.default_seek_rate, false); }
        break;
      case MOTION_MODE_LINEAR:
        // TODO: Inverse time requires F-word with each statement. Need to do a check. Also need
        // to check for initial F-word upon startup. Maybe just set to zero upon initialization
        // and after an inverse time move and then check for non-zero feed rate each time. This
        // should be efficient and effective.
        if (!axis_words) { FAIL(STATUS_INVALID_STATEMENT);} 
        else { mc_line(target[X_AXIS], target[Y_AXIS], target[Z_AXIS], 
          (gc.inverse_feed_rate_mode) ? inverse_feed_rate : gc.feed_rate, gc.inverse_feed_rate_mode); }
        break;
    }
    
    // Report any errors.
    if (gc.status_code) { return(gc.status_code); }    
    
    // As far as the parser is concerned, the position is now == target. In reality the
    // motion control system might still be processing the action and the real tool position
    // in any intermediate location.
    memcpy(gc.position, target, sizeof(target)); // gc.position[] = target[];
  }

  if (gc.program_flow) {
    plan_synchronize(); // Finish all remaining buffered motions. Program paused when complete.
    sys.auto_start = false; // Disable auto cycle start. Forces pause until cycle start issued.
    
    // If complete, reset to reload defaults (G92.2,G54,G17,G90,G94,M48,G40,M5,M9). Otherwise,
    // re-enable program flow after pause complete, where cycle start will resume the program.
    if (gc.program_flow == PROGRAM_FLOW_COMPLETED) { mc_reset(); }
    else { gc.program_flow = PROGRAM_FLOW_RUNNING; }
  }    
  
  return(gc.status_code);
}

static int next_statement(char *letter, float *float_ptr, char *line, uint8_t *char_counter) 
{
  if (line[*char_counter] == 0) {
    return(0); // No more statements
  }
  
  *letter = line[*char_counter];
  if((*letter < 'A') || (*letter > 'Z')) {
    FAIL(STATUS_EXPECTED_COMMAND_LETTER);
    return(0);
  }
  (*char_counter)++;
  if (!read_float(line, char_counter, float_ptr)) {
    FAIL(STATUS_BAD_NUMBER_FORMAT); 
    return(0);
  };
  return(1);
}








