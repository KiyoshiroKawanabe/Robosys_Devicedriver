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
作成したデバイスドライバの動画は[こちら](https://youtu.be/p71gfhBcQgs)<br>
![動画](https://user-images.githubusercontent.com/53420739/100972579-5dbfcd80-357c-11eb-821a-4fb5df8ad853.jpg)

---
## 回路  
下の画像のように回路を組みました。  
![1002793](https://user-images.githubusercontent.com/53420739/100973653-47b30c80-357e-11eb-9b09-fa11af3cbf2c.jpg)
LED赤はGPIO25,Ground 39番ピン、LED緑はGPIO22,Ground 9番ピン、電子ブザーはGPIO23,Ground 14  
にそれぞれ繋がっています。
ラズベリーパイのピン番号は[こちら](https://www.raspberrypi.org/documentation/usage/gpio/README.md)を参照してください。

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
