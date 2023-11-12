from setuptools import find_packages, setup

package_name = 'my_robot_controller'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='lukec',
    maintainer_email='luke.x.chang@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'test_node=my_robot_controller.my_first_node:main',
            'draw_circle=my_robot_controller.draw_circle:main',
            'sub_pose=my_robot_controller.pose_subscriber:main',
            'turtle_ctrl=my_robot_controller.turtle_ctrl:main',
            'py_sub=my_robot_controller.my_subscriber:main',
            'num_counter=my_robot_controller.number_counter:main',
            'add_two_ints_server=my_robot_controller.add_two_ints_server:main',
            'add_two_client1=my_robot_controller.add_two_client_1:main',
            'add_two_client2=my_robot_controller.add_two_client_2:main',
            'hw_status_publisher=my_robot_controller.hw_status_publisher:main'
        ],
    },
)
