cmake_minimum_required(VERSION 3.8)
project(omuni)

# 必要なパッケージを見つける
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# メッセージファイルの指定
set(msg_files
  "msg/Joystick.msg"
  "msg/MotorDuty.msg"
)

# メッセージのビルド設定
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES std_msgs
)

# メッセージの依存関係をエクスポート
ament_export_dependencies(rosidl_default_runtime)

# 実行可能ファイルの追加
add_executable(omuni_node src/omuni_node.cpp)

# ライブラリのリンク
ament_target_dependencies(omuni_node rclcpp std_msgs)

# メッセージの依存関係を追加
rosidl_target_interfaces(omuni_node
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

# インクルードディレクトリの指定
target_include_directories(omuni_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# インストール設定
install(TARGETS omuni_node
  DESTINATION lib/${PROJECT_NAME}
)

# メッセージのインストール
install(DIRECTORY msg
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

# 依存パッケージの指定
ament_package()