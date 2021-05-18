#include "wheels_rotation_plugin/my_plugin.h"
#include <pluginlib/class_list_macros.h>
#include <QStringList>

namespace wheels_rotation_plugin
{
MyPlugin::MyPlugin()
  : rqt_gui_cpp::Plugin()
  , widget_(0)
{
  setObjectName("MyPlugin");
}


void MyPlugin::initPlugin(qt_gui_cpp::PluginContext& context)
{
  QStringList argv = context.argv();
  file_path = __FILE__;
  file_path = file_path.substr(0, file_path.rfind("/src")); 
  file_path+="/config/saved_topic.txt";
  save_file.open(file_path,std::ios::in | std::ios::out);
  
  if(!save_file.is_open())
  {
    ROS_INFO("!");
  }
  save_file>>pickedTopic;
  std::string sTopic="Saved Topic: ";
  sTopic+=pickedTopic;
  widget_ = new QMainWindow();
  nh=getNodeHandle();
  ui_.setupUi(widget_);
        ui_.topic_label->setText(QString::fromStdString(sTopic));
        save_file.close();
        scene = new QGraphicsScene(this);
        timer_1 = new QTimer(this);
        ui_.graphicsView->setScene(scene);
        float edges[][2] = { {-65,-12.5},{-65,162.5},{140,-12.5},{140,162.5} };//x,y
        int wheel_w=25,wheel_h=50;
        QBrush greenBrush(Qt::green);
        QBrush whiteBrush(Qt::white);
        QPen outlinePen(Qt::black);
        outlinePen.setWidth(2);
        wheels[0]= scene->addRect(edges[0][0], edges[0][1], wheel_w, wheel_h, outlinePen,whiteBrush);
        wheels[1]= scene->addRect(edges[1][0], edges[1][1], wheel_w, wheel_h, outlinePen,whiteBrush);
        wheels[2]= scene->addRect(edges[2][0], edges[2][1], wheel_w, wheel_h, outlinePen,whiteBrush);
        wheels[3]= scene->addRect(edges[3][0], edges[3][1], wheel_w, wheel_h, outlinePen,whiteBrush);
        rectangle[0] = scene->addRect(0, 0, 100, 200, outlinePen, whiteBrush);
        rectangle[1] = scene->addRect(-50, 0, 50, 25, outlinePen, whiteBrush);
        rectangle[2] = scene->addRect(-50, 175, 50, 25, outlinePen, whiteBrush);
        rectangle[3] = scene->addRect(100, 0, 50, 25, outlinePen, whiteBrush);
        rectangle[4] = scene->addRect(100, 175, 50, 25, outlinePen, whiteBrush);
        updateTopics();
        for(int i=0;i<4;i++)
        {
          wheels[i]->setTransformOriginPoint(edges[i][0]+(wheel_w/2),edges[i][1]+(wheel_h/2));
        }
        if(checkTopics())
        {
          subscribe_topic(pickedTopic);
        }
        

        topic_present=checkTopics();
        connect(timer_1,&QTimer::timeout,this,&MyPlugin::rotate_w);
        timer_1->start(10);
        connect(ui_.topics_names,&QComboBox::currentTextChanged,this,&MyPlugin::on_topicChange);
        connect(ui_.refreshButton,&QPushButton::clicked,this,&MyPlugin::updateTopics);

  
  context.addWidget(widget_);
}

void MyPlugin::on_topicChange()
{
  std::ofstream ofs;
  ofs.open(file_path, std::ofstream::out | std::ofstream::trunc);
  
  QString qss=ui_.topics_names->currentText();
  pickedTopic=qss.toUtf8().constData();
  ofs<<pickedTopic;
  ofs.close();
  std::string sTopic="Saved Topic: ";
  sTopic+=pickedTopic;
  ui_.topic_label->setText(QString::fromStdString(sTopic));
  subscribe_topic(pickedTopic);

}

void MyPlugin::updateTopics()
{
  ros::master::V_TopicInfo master_topics;
  ros::master::getTopics(master_topics);
  QString QsTopic;
  ui_.topics_names->clear();
  for (ros::master::V_TopicInfo::iterator it = master_topics.begin() ; it != master_topics.end(); it++) {
    const ros::master::TopicInfo& info = *it;
    if(info.datatype=="sensor_msgs/JointState")
    {
      QsTopic=QString::fromStdString(info.name);
      ui_.topics_names->addItem(QsTopic);
    }
  }
}

bool MyPlugin::checkTopics()
{

  ros::master::V_TopicInfo master_topics;
  ros::master::getTopics(master_topics);

  for (ros::master::V_TopicInfo::iterator it = master_topics.begin() ; it != master_topics.end(); it++) {
    const ros::master::TopicInfo& info = *it;
    if(info.name==pickedTopic)
    {
       return true;
    }
  }
  return false;

}

void MyPlugin::rotate_w()
{
  topic_present=checkTopics();
  if(topic_present==true)
  {
    QString Qtext_p[4];
    for(int i=0;i<4;i++)
    {
      Qtext_p[i]= QString("Rot=%1").arg(pos[i]);
    }
    ui_.pos_text_1->setText(Qtext_p[0]);
    ui_.pos_text_2->setText(Qtext_p[1]);
    ui_.pos_text_3->setText(Qtext_p[2]);
    ui_.pos_text_4->setText(Qtext_p[3]);


    {
      std::lock_guard<std::mutex>lock(pos_vector_lock);
      for(int i=0;i<4;i++)
      {
        wheels[i]->setRotation(pos[i]);
      }
    }
      
  }

}

void MyPlugin::subscribe_topic(std::string topic)
{
  sub.shutdown();
  sub = nh.subscribe(topic, 100, &MyPlugin::posInfoCallback, this);
}

void MyPlugin::posInfoCallback(const sensor_msgs::JointState::ConstPtr& msg)
{
    float raw_pos[4];
    int i=0;
    for(auto it = begin(msg->position); it != end(msg->position); ++it)
    {
      for(int j=0;j<4;j++)
      {
        if(msg->name[i]==wheel_names[j])
        {
          std::lock_guard<std::mutex>lock(pos_vector_lock);
          raw_pos[j]=msg->position[i];
          raw_pos[j]=raw_pos[j]*57.29;
          pos[j]=raw_pos[j];        
        }
      }
      i++;
    }
    if(!checkTopics())
    {
      sub.shutdown();
      ROS_INFO("Topic lost!");
    }
}



void MyPlugin::shutdownPlugin()
{
  sub.shutdown();
  save_file.close();
}

void MyPlugin::saveSettings(qt_gui_cpp::Settings& plugin_settings,
    qt_gui_cpp::Settings& instance_settings) const
{
  
}

void MyPlugin::restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
    const qt_gui_cpp::Settings& instance_settings)
{
  
}


}  // namespace wheels_rotation_plugin
PLUGINLIB_EXPORT_CLASS( wheels_rotation_plugin::MyPlugin, rqt_gui_cpp::Plugin)


