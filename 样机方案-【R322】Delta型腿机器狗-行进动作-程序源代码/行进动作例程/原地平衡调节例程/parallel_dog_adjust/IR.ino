/*****红外避障相关代码*****/

//红外检测开关
bool _irSwitch = true;

void enableIR()
{
	_irSwitch = true;
}
void disableIR()
{
	_irSwitch = false;
}

//红外传感器初始化
void IRInit()
{
	pinMode(LEFT_IR_PIN, INPUT);
	pinMode(RIGHT_IR_PIN, INPUT);
	pinMode(BACK_IR_PIN, INPUT);
	enableIR();
}

//红外更新
void updateIR()
{
	if (!_irSwitch) return;

	bool left = !digitalRead(LEFT_IR_PIN); // 左侧红外状态
	bool right = !digitalRead(RIGHT_IR_PIN); // 右侧红外状态
	bool back = !digitalRead(BACK_IR_PIN); // 后面红外传感器状态

	if (left && right && back)
	{
		dogReset({0, 0, Leg_Init_Z_Pos}, 1000);
	}
	else if (left && right) {
		resetCycleCount();
		setMode(DOG_MODE_BACK);
	}
	else if (back && left)
	{
		resetCycleCount();
		setMode(DOG_MODE_RIGHT);
	}
	else if (back && right)
	{
		resetCycleCount();
		setMode(DOG_MODE_LEFT);
	}
	else if (right) {
		resetCycleCount();
		setMode(DOG_MODE_TURN_LEFT);
	}
	else if (left) {
		resetCycleCount();
		setMode(DOG_MODE_TURN_RIGHT);
	}
	else if (back) {
		resetCycleCount();
		setMode(DOG_MODE_FRONT);
	}
	else if (!left && !right && !back)
	{
		setMode(DOG_MODE_FRONT);
	}
}


