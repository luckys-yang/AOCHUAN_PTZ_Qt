#pragma once
#ifndef PROTOCOL_H
#define PROTOCOL_H

/*===============================  旧协议1 宏 ================================*/
/*帧头*/
enum Protocol1_FrameHeader_rt
{
	PRO1_FrameHead = 0x55	// 0x55
};
/*地址*/
enum Protocol1_Addr_et
{
	PRO1_Pitch = 0x01,	// 俯仰/云台0x01
	PRO1_Roll = 0x02,	//  横滚(仅Bootloader 状态有效)0x02
	PRO1_Yaw = 0x03,	// 航向(仅Bootloader 状态有效)0x03
	PRO1_Handle = 0x04,	// 手柄/网关0x04
	PRO1_Gate1 = 0x0B,	// 网关1号端口0x0B
	PRO1_Gate2 = 0x0C,	// 网关2号端口0x0C
	PRO1_Camera = 0x0D,	// 摄像头0x0D
	PRO1_RemoteCOntrol = 0x0E,	// 遥控器0x0E
};


/*功能码*/
enum Protocol1_FunctionCode_et
{
	PRO1_FUNC_Verify = 0x00,	// 0x00确认命令
	PRO1_FUNC_Deny = 0x01,	// 0x01否认命令
	PRO1_FUNC_DebugCmd = 0x02,	// 0x02调试命令
	PRO1_FUNC_SixCalibrationNextStep = 0x03,	// 0x03六面校准下一步
	PRO1_FUNC_MotorTestAttitudeSet = 0x11,	// 0x11电机测试-姿态 设置
	PRO1_FUNC_UniformMotionSet = 0x13,	// 0x13匀速运动-速度 设置
	PRO1_FUNC_AttitudeFineTuningGet = 0x15,	// 0x15 姿态微调 - 读取
	PRO1_FUNC_AttitudeFineTuningSet = 0x16,	// 0x15 姿态微调 - 设置
	PRO1_FUNC_FollowParameterGet = 0x17,	// 0x17 跟随参数 - 获取
	PRO1_FUNC_QuickFollow = 0x18,	// 0x18 快速跟随
	PRO1_FUNC_FollowParameterSet = 0x19,	// 0x19 跟随参数 - 设置
	PRO1_FUNC_ControlParameterGet = 0x1A,	// 0x1A 控制参数 获取
	PRO1_FUNC_ControlParameterSet = 0x1B,	// 0x1B 控制参数 设置
	PRO1_FUNC_UniformMotionQuery = 0x1E,	// 0x1E 匀速运动速度 查询
	PRO1_FUNC_ParameterDefault = 0x1F,	// 0x1F 跟随参数/控制参数 缺省
	PRO1_FUNC_TrackMode = 0x22,	// 0x22 轨迹模式
	PRO1_FUNC_HVSwitch = 0x25,	// 0x25 HV横竖切换
	PRO1_FUNC_LeftNoneRightControl = 0x26,	// 0x26 左/无/右 控制
	PRO1_FUNC_MotorZeroPositionQuery = 0x27,	// 0x27 电机零位置微调 查询
	PRO1_FUNC_MotorZeroPositionSet = 0x28,	// 0x28 电机零位置微调 设置
	PRO1_FUNC_SelfieReturnCenter = 0x30,	// 0x30自拍/ 回中
	PRO1_FUNC_RunControl = 0x31,	// 0x31开始全景/执行全景/退出全景  盗梦 dm1启/dm1执行/dm1退
	PRO1_FUNC_PostureQuery = 0x10,		// 0x10姿态查询 - 下位机回复姿态信息
	PRO1_FUNC_MotorTestTorqueSet = 0x40,		// 0x40电机测试-力矩 设置
	PRO1_FUNC_RebootCalibrationClear = 0x45,	// 0x45重启/校准清除
	PRO1_FUNC_Interim_Order = 0x46,	// 0x46临时命令-声音 - 发送给下位机  辨识采样
	PRO1_FUNC_RollLed = 0x49,	// 0x49 补光灯控制
	PRO1_FUNC_UserDataRead = 0x4A,	// 0x4A 用户数据UD读
	PRO1_FUNC_UserDataWrite = 0x4B,	// 0x4B 用户数据UD写
	PRO1_FUNC_PTZTestNoise = 0x4C,	// 0x4C PTZ云台测试 噪声
	PRO1_FUNC_VersionQuery = 0x50,	// 0x50版本查询 -- 下位机回复版本信息
	PRO1_FUNC_SystemStatusQuery = 0x51,		// 0x51系统状态查询 -- 下位机回复系统状态信息
	PRO1_FUNC_ShutDown = 0x52,		// 0x52关机
	PRO1_FUNC_MotorCalibration = 0x53,	// 0x53电机校准
	PRO1_FUNC_AttitudeCalibration = 0x54,	// 0x54姿态校准
	PRO1_FUNC_ControlPIDSet = 0x56,	// 0x56 控制PID 设置
	PRO1_FUNC_ControlPIDQuery = 0x57,	// 0x57 控制PID 查询
	PRO1_FUNC_SixCalibration = 0x58,	// 0x58六面校准
	PRO1_FUNC_ReadHall = 0xA1,	// 0xA1读霍尔
};

// 定义系统状态位域结构体(上到下是低位到高位，小端模式 31位有用1位保留)
struct Protocol1_SystemStatus_st 
{
	unsigned int calibration_step : 3;  // 校准状态(0:无 1: 电机校准 2: 姿态校准 3: 六面校准)
	unsigned int calibration_status : 4;  // 校准步骤(0: 校准开始 10: 校准完成 11: 校准超时 12~15: 校准错误【电机校准】- 1: 校准航向 2: 校准横滚 3: 校准俯仰 【姿态校准】- 1: 等待静止 2: 计算)
	unsigned int gyro_exception : 1;          // 陀螺仪异常(0: 正常 1: 异常)
	unsigned int yaw_axis_comm_exception : 1;      // 航向轴通信异常(0: 正常 1: 异常)
	unsigned int roll_axis_comm_exception : 1;         // 横滚轴通信异常
	unsigned int motor_zero_angle_not_calibrated : 1;   // 电机零角度未校准
	unsigned int accelerometer_not_calibrated : 1;     // 加速度计未校准
	unsigned int gyro_not_calibrated : 1;               // 陀螺仪未校准
	unsigned int motor_not_calibrated : 1;              // 电机未校准
	unsigned int reserved : 1;                          // 保留
	unsigned int run_mode : 3;                          // 运行模式(0: 普通模式 1: 校准模式)
	unsigned int roll_encoder_error : 1;                // 横滚编码器错误
	unsigned int pitch_encoder_error : 1;               // 俯仰编码器错误
	unsigned int yaw_encoder_error : 1;             // 航向编码器错误
	unsigned int motor_overheat_warning : 1;            // 电机高温报警
	unsigned int block_warning : 1;                     // 阻塞报警
	unsigned int motor_angle_protection : 1;            // 电机角度保护
	unsigned int roll_following : 1;                    // 横滚跟随
	unsigned int pitch_following : 1;                   // 俯仰跟随
	unsigned int yaw_following : 1;                 // 航向跟随
	unsigned int vertical_shoot_mode : 1;               // 竖拍模式
	unsigned int status : 2;                            // 状态(0: 初始状态 1: 运行状态 2: 关机状态 3: 快速关机状态)
	unsigned int controller_rebooting : 1;              // 控制器重启中
	unsigned int external_control_allowed : 1;          // 外部控制允许
};

// 定义扩展状态位域结构体(上到下是低位到高位，小端模式 32位有用 0位保留)
struct Protocol1_ExtendedStatus_st
{
	unsigned int posture_shift_state : 1;	// 姿态移动状态(0: 无位移或已完成 1: 执行中)
	unsigned int path_mode : 2;	// 轨迹模式(0: 非轨迹模式 1: 轨迹准备阶段 2: 轨迹执行阶段 3: 轨迹执行完成)
	unsigned int path_running_whether_reached_start : 1;	// 轨迹运行是否进入了开始位置(0: 未到开始位置 1: 已到达开始位置)
	unsigned int work_mode : 2;	// 工作模式(用于向后台/APP提供控制模式)(0: 普通模式 1: 疯狗模式 2: 全向跟随模式 3: POV 4： DV(POV模式下的盗梦))
	unsigned int extended_mode_notification : 2;	// 扩展模式通知(0: NONE 1: 全景模式)
	unsigned int app_mode : 8;	// 应用模式(0：无 1：盗梦空间模式 2：广角模式 3：自拍模式 4：盗梦空间1模式 5：自主全景模式 6：云台跟踪模式)
	unsigned int app_mode_running_data_speed : 8;	// 应用模式下的运行数据 - 速度
	unsigned int app_mode_running_data_step : 8;	// 应用模式下的运行速度 - 步骤(当前步骤 0：准备 1：准备完成 2：开始 3：执行中 4：执行完成)
};

// 定义内部状态位域结构体(上到下是低位到高位，小端模式 20位有用 12位保留)
struct Protocol1_InsideStatus_st
{
	unsigned int motor_still_flag_x : 1;	// X电机静止标志(0：非静止 1：静止)
	unsigned int motor_still_flag_y : 1;	// Y电机静止标志(0：非静止 1：静止)
	unsigned int motor_still_flag_z : 1;	// Z电机静止标志(0：非静止 1：静止)
	unsigned int external_moment_flag_x : 1;	// 外部力矩标志X(0：无力矩 1：有力矩)
	unsigned int external_moment_flag_y : 1;	// 外部力矩标志Y(0：无力矩 1：有力矩)
	unsigned int external_moment_flag_z : 1;	// 外部力矩标志Z(0：无力矩 1：有力矩)
	unsigned int stalled_flag_x : 1;	// 堵转标志X
	unsigned int stalled_flag_y : 1;	// 堵转标志Y
	unsigned int stalled_flag_z : 1;	// 堵转标志Z
	unsigned int running_mode_revise : 1;	// 运行模式修改
	unsigned int vertical_horizontal_switching : 1;	// 竖横屏切换中
	unsigned int euler_angle_calculation_switching : 1;	// 欧拉角计算切换中
	unsigned int flashlight_mode : 1;	// 是否为手电筒模式
	unsigned int handle_handstand : 1;	 // 手柄是否倒立
	unsigned int reserved1 : 2;	// 保留
	unsigned int calibration_operations_allowed : 1;	// 校准操作允许
	unsigned int ai_camera_online : 1;	// AI摄像头在线
	unsigned int reserved2 : 1;	// 保留位
	unsigned int external_horizontal_vertical_shot_switch: 1;	// 外部横竖拍切命令
	unsigned int reserved3 : 12;	// 保留位
};


#endif