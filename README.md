# Robosys_Devicedriver
ロボットシステム学の課題１

---
## 概要
青信号の時,音が鳴る歩行者信号をLEDを信号に見立てて作成しました。  
[上田隆一教授が授業で作成したデバイスドライバ](https://github.com/ryuichiueda/robosys_device_drivers/blob/master/myled.c)を改変したものです。  
コードは佐藤暖君のを参考にしました。

---
## 動作環境  
OS:Ubuntu 18.04  
---
## 使用したもの
・Raspberry Pi 4 ModelB  
・ブレッドボード  
・5mm LED 赤、緑  
・ジャンパー線F-M ×4  
・220Ω抵抗器 ×2  
・電子ブザー  

---
## デモ動画
作成したデバイスドライバの動画は[こちら](https://youtu.be/p71gfhBcQgs)<br>
![動画](https://user-images.githubusercontent.com/53420739/100972579-5dbfcd80-357c-11eb-821a-4fb5df8ad853.jpg)

---
## 回路  
下の画像のように回路を組みました。  
<img src="https://user-images.githubusercontent.com/53420739/100973653-47b30c80-357e-11eb-9b09-fa11af3cbf2c.jpg" width="320px">  
LED赤はGPIO25,Ground 39番ピン  
LED緑はGPIO22,Ground 9番ピン  
電子ブザーはGPIO23,Ground 14番ピン    
にそれぞれ繋がっています。  
LEDは足が長い方、電子ブザーは＋の方をGPIOに接続してください。  
ラズベリーパイのピン番号は[こちら](https://www.raspberrypi.org/documentation/usage/gpio/README.md)を参照してください。

---
## インストール方法  
```
$ git clone https://github.com/kiyoshirou-kawanabe/Robosys_Devicedriver.git  
```
---
## ビルド、実行
### ビルド
```
$ make  
$ cd Robosys_Devicedriver/myled  
$ sudo insmod myled.ko  
$ sudo chmod 666 /dev/myled0  
```  
### 実行

以下のコードを入力すると実行できます。 
```
$echo a >> /dev/myled0  
```
---
## ライセンス
[GNU General Public License v3.0](https://github.com/kiyoshirou-kawanabe/Robosys_Devicedriver/blob/main/COPYING)
