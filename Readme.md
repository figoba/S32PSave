<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
## S32P Save software
#更新说明

1. 2018-07-20 git方式管理启用，增加工单数量超过提醒，版本号升级为1.30
2. 2018-07-28 修正保存的S32P文件名与SN之间的对应关系，由原来的相同改为将SN中的非法文件名字符映射为"-"，写入EEPROM芯片里面的SN保持原样不变，不做映射，版本号升级为1.31
