#include "CMDDialog.h"
#include "ui_CMDDialog.h"

CMDDialog::CMDDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CMDDialog)
{
    ui->setupUi(this);
    ALNum_ROScommand = PODOALDialog::GetALNumFromFileName("ROScommand");

//    connect(pLAN, SIGNAL(NewPODOData()), this, SLOT(DisplayUpdate()));

    ui->JOY_TABLE_INFO_LEFT->setColumnWidth(0, 60);
    ui->JOY_TABLE_INFO_RIGHT->setColumnWidth(0, 60);

    displayTimer = new QTimer(this);
    connect(displayTimer, SIGNAL(timeout()), this, SLOT(DisplayUpdate()));
    displayTimer->start(50);//50
}

CMDDialog::~CMDDialog()
{
    delete ui;
}
void CMDDialog::DisplayUpdate()
{
    // Data Show
    QString str;
    QTableWidgetItem *tempItem;
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_LT));
    ui->JOY_TABLE_INFO_LEFT->setItem(0,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_LB));
    ui->JOY_TABLE_INFO_LEFT->setItem(1,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_LJOG_RL));
    ui->JOY_TABLE_INFO_LEFT->setItem(2,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_LJOG_UD));
    ui->JOY_TABLE_INFO_LEFT->setItem(3,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_AROW_RL));
    ui->JOY_TABLE_INFO_LEFT->setItem(4,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_AROW_UD));
    ui->JOY_TABLE_INFO_LEFT->setItem(5,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_RJOG_PUSH));
    ui->JOY_TABLE_INFO_LEFT->setItem(6,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_LJOG_PUSH));
    ui->JOY_TABLE_INFO_LEFT->setItem(7,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_BACK));
    ui->JOY_TABLE_INFO_LEFT->setItem(8,0,tempItem);

    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_RT));
    ui->JOY_TABLE_INFO_RIGHT->setItem(0,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_RB));
    ui->JOY_TABLE_INFO_RIGHT->setItem(1,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_RJOG_RL));
    ui->JOY_TABLE_INFO_RIGHT->setItem(2,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_RJOG_UD));
    ui->JOY_TABLE_INFO_RIGHT->setItem(3,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_Y));
    ui->JOY_TABLE_INFO_RIGHT->setItem(4,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_X));
    ui->JOY_TABLE_INFO_RIGHT->setItem(5,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_B));
    ui->JOY_TABLE_INFO_RIGHT->setItem(6,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_A));
    ui->JOY_TABLE_INFO_RIGHT->setItem(7,0,tempItem);
    tempItem = new QTableWidgetItem(); tempItem->setText(str.sprintf("%d", PODO_DATA.joy_value.JOY_START));
    ui->JOY_TABLE_INFO_RIGHT->setItem(8,0,tempItem);



}

void CMDDialog::on_BTN_WALKREADY_clicked()
{
    USER_COMMAND cmd;
    cmd.COMMAND_TARGET = ALNum_ROScommand;
    cmd.COMMAND_DATA.USER_COMMAND = BASICCMD_WALKREADY;
    pLAN->SendCommand(cmd);
}

void CMDDialog::on_BTN_HOMEPOS_clicked()
{
    USER_COMMAND cmd;
    cmd.COMMAND_TARGET = ALNum_ROScommand;
    cmd.COMMAND_DATA.USER_COMMAND = BASICCMD_HOMEPOS;
    pLAN->SendCommand(cmd);
}

void CMDDialog::on_BTN_GRIPPER_OPEN_clicked()
{
    USER_COMMAND cmd;
    cmd.COMMAND_TARGET = ALNum_ROScommand;
    cmd.COMMAND_DATA.USER_COMMAND = BASICCMD_GRIPPER;

    if(ui->RB_BOTH->isChecked())
        cmd.COMMAND_DATA.USER_PARA_INT[1] = GUI_GRIPPER_BOTH;
    else if(ui->RB_RH->isChecked())
        cmd.COMMAND_DATA.USER_PARA_INT[1] = GUI_GRIPPER_RIGHT;
    else if(ui->RB_LH->isChecked())
        cmd.COMMAND_DATA.USER_PARA_INT[1] = GUI_GRIPPER_LEFT;

    cmd.COMMAND_DATA.USER_PARA_INT[0] = GUI_GRIPPER_OPEN;
    cmd.COMMAND_DATA.USER_PARA_DOUBLE[0] = ui->LE_GRIPPER_INPUT->text().toDouble();
    pLAN->SendCommand(cmd);
}


void CMDDialog::on_BTN_GRIPPER_STOP_clicked()
{
    USER_COMMAND cmd;
    cmd.COMMAND_TARGET = ALNum_ROScommand;
    cmd.COMMAND_DATA.USER_COMMAND = BASICCMD_GRIPPER;

    if(ui->RB_BOTH->isChecked())
        cmd.COMMAND_DATA.USER_PARA_INT[1] = GUI_GRIPPER_BOTH;
    else if(ui->RB_RH->isChecked())
        cmd.COMMAND_DATA.USER_PARA_INT[1] = GUI_GRIPPER_RIGHT;
    else if(ui->RB_LH->isChecked())
        cmd.COMMAND_DATA.USER_PARA_INT[1] = GUI_GRIPPER_LEFT;

    cmd.COMMAND_DATA.USER_PARA_INT[0] = GUI_GRIPPER_STOP;
    cmd.COMMAND_DATA.USER_PARA_DOUBLE[0] = ui->LE_GRIPPER_INPUT->text().toDouble();
    pLAN->SendCommand(cmd);
}

void CMDDialog::on_BTN_GRIPPER_CLOSE_clicked()
{
    USER_COMMAND cmd;
    cmd.COMMAND_TARGET = ALNum_ROScommand;
    cmd.COMMAND_DATA.USER_COMMAND = BASICCMD_GRIPPER;

    if(ui->RB_BOTH->isChecked())
        cmd.COMMAND_DATA.USER_PARA_INT[1] = GUI_GRIPPER_BOTH;
    else if(ui->RB_RH->isChecked())
        cmd.COMMAND_DATA.USER_PARA_INT[1] = GUI_GRIPPER_RIGHT;
    else if(ui->RB_LH->isChecked())
        cmd.COMMAND_DATA.USER_PARA_INT[1] = GUI_GRIPPER_LEFT;

    cmd.COMMAND_DATA.USER_PARA_INT[0] = GUI_GRIPPER_CLOSE;
    cmd.COMMAND_DATA.USER_PARA_DOUBLE[0] = ui->LE_GRIPPER_INPUT->text().toDouble();
    pLAN->SendCommand(cmd);
}

void CMDDialog::on_BTN_JOYSTART_clicked()
{
    USER_COMMAND cmd;
    cmd.COMMAND_TARGET = ALNum_ROScommand;
    cmd.COMMAND_DATA.USER_COMMAND = MANUALCMD_JOYON;
    cmd.COMMAND_DATA.USER_PARA_INT[0] = JOY_ON;
    pLAN->SendCommand(cmd);
}

void CMDDialog::on_BTN_JOYSTOP_clicked()
{
    USER_COMMAND cmd;
    cmd.COMMAND_TARGET = ALNum_ROScommand;
    cmd.COMMAND_DATA.USER_COMMAND = MANUALCMD_JOYON;
    cmd.COMMAND_DATA.USER_PARA_INT[0] = JOY_OFF;
    pLAN->SendCommand(cmd);
}

void CMDDialog::on_BTN_JOYMOVE_clicked()
{
    USER_COMMAND cmd;
    cmd.COMMAND_TARGET = ALNum_ROScommand;
    cmd.COMMAND_DATA.USER_COMMAND = MANUALCMD_JOYMOVE;
    cmd.COMMAND_DATA.USER_PARA_INT[0] = JOY_START;
    pLAN->SendCommand(cmd);
}

void CMDDialog::on_BTN_MOVESTOP_clicked()
{
    USER_COMMAND cmd;
    cmd.COMMAND_TARGET = ALNum_ROScommand;
    cmd.COMMAND_DATA.USER_COMMAND = MANUALCMD_JOYMOVE;
    cmd.COMMAND_DATA.USER_PARA_INT[0] = JOY_STOP;
    pLAN->SendCommand(cmd);
}

void CMDDialog::on_pushButton_clicked()
{
    USER_COMMAND cmd;
    cmd.COMMAND_TARGET = ALNum_ROScommand;
    cmd.COMMAND_DATA.USER_COMMAND = BASICCMD_SAVE;
    pLAN->SendCommand(cmd);
}
