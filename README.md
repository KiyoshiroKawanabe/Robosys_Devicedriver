# Robosys_Devicedriver
ロボットシステム学の課題１

---
## 内容 
青信号の時音が鳴る歩行者信号をLEDを信号に見立てて作成しました。  
[上田隆一教授が授業で作成したデバイスドライバ](https://github.com/ryuichiueda/robosys_device_drivers/blob/master/myled.c)を改変したものです。

---
## 使用したもの
・Raspberry Pi 4 ModelB  
・ブレッドボード  
・5mm LED 赤、緑  
・ジャンパー線F-M ×４  
・220Ω抵抗器 ×２  
・電子ブザー  

---
## 動画
作成したデバイスドライバの動画は[こちら](https://youtu.be/p71gfhBcQgs)

---
## ビルド、実行
### ビルド
```
＄ git clone https://github.com/kiyoshirou-kawanabe/Robosys_Devicedriver.git  
＄ cd Robosys_Devicedriver/myled  
＄ sudo insmod myled.ko  
＄ sudo chmod 666 /dev/myled0  
＄ echo a >> /dev/myled0  
```  
### 実行
```  
以下のコードを入力すると実行できます。  
＄echo a >> /dev/myled0  
