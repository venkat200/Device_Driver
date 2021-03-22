cmd_/home/ubuntu/Desktop/Folder/modules.order := {   echo /home/ubuntu/Desktop/Folder/MyKernalModule.ko; :; } | awk '!x[$$0]++' - > /home/ubuntu/Desktop/Folder/modules.order
