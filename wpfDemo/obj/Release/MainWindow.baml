   M S B A M L   `   `   `  ����   wpfDemo    wpfDemo.MainWindow   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     -     �Name$  
mainWindow�� � Title$ 
MainWindow��$	��350��$	��525��$��14(� � WindowStyle$ ThreeDBorderWindow=� � 	Resources  �� MergedDictionaries �� Source��  �� $ CommonStyle.xaml?�%    .��� $��5q� � UseLayoutRounding . ���� .���  � Offset$ 0Q� � Color$ 
LightGreen��� $	 0.5Q�$ 	LightBlue��	 � RowDefinitions	 �� $��35 ��� $��50 ��� $��35 ��� $��50 ��� $��50 ��� 
 � ColumnDefinitions
 �� $��6* ��� $��* ��� $��* �.+��� $��0��.��VisaAddress�� $��1��$��0��.��#!TCPIP0::LOCALHOST::hislip0::INSTR�� $��2��$��3��$��0��.��
SavePath�� -   $��TxtFilePath��$��3��$��0������  �� ElementName$ 
mainWindow�� �� Path$ Counter��� -   $��	BtnBrowse��$	��...��$��2��$
��Left=�$��44��$��2,2,2,2q�$��3��$��Bottom=��� $��4��$��0�� �� Orientation$ 
Horizontal=�.+��� -   $��
chkConnect��$��0,0,10,0q�.��	Connect�� .���� .+�	� $	��snp�� 	� 	GroupName$ fileType��	� $��	pure data��$ fileType���� -   $��btnSave��$��4��$��2��.��Save�� $��5��$��0��$��3��$��3q� �� Padding$ 3q�
����ح�
���E��$��2q� �� CornerRadius$ 3��._��� -   $��rtStatus��$��20q�