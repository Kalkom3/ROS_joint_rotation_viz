#ifndef wheels_rotation_plugin_MY_PLUGIN_H
#define wheels_rotation_plugin_MY_PLUGIN_H


#include <rqt_gui_cpp/plugin.h>
#include <ros/package.h>
#include <ros/master.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <mutex>

#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "argo_gui/ui_my_plugin.h"

#include <QGraphicsItem>
#include <QWidget>
#include <QAction>
#include <QList>
#include <QLabel>
#include <QString>
#include <QSet>
#include <QSize>
#include <QTimer>

#include <vector>

namespace wheels_rotation_plugin
{

class MyPlugin
  : public rqt_gui_cpp::Plugin
{
  Q_OBJECT
public:
  MyPlugin();
  virtual void initPlugin(qt_gui_cpp::PluginContext& context);
  virtual void shutdownPlugin();
  virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings,
      qt_gui_cpp::Settings& instance_settings) const;
  virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
      const qt_gui_cpp::Settings& instance_settings);
      void rotate_w();

private:
  std::mutex pos_vector_lock;
  std::fstream save_file;
  std::string file_path;
  ros::NodeHandle nh;
  ros::Subscriber sub;
  bool topic_present=false;
  std::string wheel_names[4]={"wheel1","wheel2","wheel3","wheel4"};
  int pos[4]={0,0,0,0};
  Ui::MainWindow ui_;
  QMainWindow* widget_;
  QTimer *timer_1;
  QGraphicsScene *scene;
  QGraphicsRectItem *rectangle[5];
  QGraphicsRectItem *wheels[4];
  QGraphicsTextItem *text;
  std::string pickedTopic;
  void posInfoCallback(const sensor_msgs::JointState::ConstPtr& msg);
  void subscribe_topic(std::string topic);
  void on_topicChange();
  void receive_mes();
  void updateTopics();
  bool checkTopics();
};
}  // namespace wheels_rotation_plugin
#endif  // wheels_rotation_plugin_MY_PLUGIN_H
