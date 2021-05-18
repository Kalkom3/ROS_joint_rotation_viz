Plugin name: wheels_rot_viz


Descrition: Read rotation data from topic and vizualise positon of wheels(4). 
  Topic is picked by seting name in comboBox and pressing OK button.
  REFRESH button reset topics list avaliable for plugin.


Message type sensor_msg/JointState:  
string[] name  
float64[] position  
float64[] velocity  
float64[] effort  


Testing publisher name: Transmiter (alternative)name