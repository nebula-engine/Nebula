#/bin/bash

echo ps aux

ps aux | grep "./test_server_no_gui"
ps aux | grep "../test/server_no_gui"

echo cleanup start

kill $(ps aux | grep "./test_server_no_gui" | awk '{print $2}')
kill $(ps aux | grep "../test/server_no_gui" | awk '{print $2}')

echo cleanup finish

ps aux | grep "./test_server_no_gui"
ps aux | grep "../test/server_no_gui"

