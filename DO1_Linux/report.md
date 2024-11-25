## Part 1  
- версия 20.04  
![part](screen/part1.png)  
## Part 2  
- Скриншот команд  
![part](screen/part2-1.png) 
- Скриншот cat /etc/passwd
![part](screen/part2-2.png)  
## Part 3  
- заходим в hostname  
![part](screen/part3-0.png)  
- задаем название машины  
![part](screen/part3-1.png)  
- меняем таймзону
![part](screen/part3-2.png)  
- название сетевого интерфейса  
![part](screen/part3-3.png)  
- Один из самых основных виртуальных интерфейсов - lo. Это локальный интерфейс, который позволяет программам обращаться к этому компьютеру. Используя консольную команду получить ip адрес устройства, на котором вы работаете, от DHCP сервера.  
- скачивание dhcp сервера  
![part](screen/part3-4.png)   
- ifconfig
![part](screen/part3-5.png)  
- DHCP - это клиент-серверный протокол динамической конфигурации хоста (Dynamic Host Configuration Protocol), с помощью которого в ИТ-инфраструктуре сетевые параметры каждого нового устройства прописываются автоматически.  
- статичные настройки вручную задаются  
![part](screen/part3-6.png)  
![part](screen/part3-7.png)  
- после перезагрузки  
![part](screen/part3-8.png)    
## Part 4  
- обновление системы пакетов  
![part](screen/part4.png)  
## Part 5  
- поменять hostname от имени пользователя  
![part](screen/part5-1.png)  
![part](screen/part5-2.png)  
- измененный hostname  
![part](screen/part5-3.png)
- sudo -это утилита, она позволяет временно поднимать привилегии и выполнять задачи администрирования системы  
## Part 6  
- вывести время часового пояса  
![part](screen/part6-1.png)  
- содержит NTPSynchronized=yes: timedatectl show
![part](screen/part6-2.png)  
## Part 7  
- установление пакетов  
![part](screen/part7-1.png)  
 - создание файла nano  
![part](screen/part7-2.png)  
- файл с ником  
![part](screen/part7-3.png)  
- vim файл  
![part](screen/part7-4.png)  
- mcedit файл  
![part](screen/part7-5.png)  
![part](screen/part7-6.png)  
- отредактировать на 21 School 21  
![part](screen/part7-7.png)  
- отредактировать на 21 School 21  
![part](screen/part7-8.png)  
- отредактировать на 21 School 21  
![part](screen/part7-9.png)  
- Используя каждый из трех выбранных редакторов, отредактируйте файл ещё раз (по аналогии с предыдущим пунктом), а затем освойте функции поиска по содержимому файла (слово) и замены слова на любое другое.  
- vim поиск  
![part](screen/part7-10.png)  
- замена  
![part](screen/part7-11.png)  
- nano поиск  
![part](screen/part7-12.png)  
- замена  
![part](screen/part7-13.png)  
![part](screen/part7-14.png)  
- mcedit поиск  
![part](screen/part7-15.png)  
![part](screen/part7-16.png)  
- замена  
![part](screen/part7-17.png)  
![part](screen/part7-18.png)  
![part](screen/part7-19.png)  
## Part 8  
- установить sshd
![part](screen/part8-1.png)  
- автостарт службы при загрузке системы  
![part](screen/part8-2.png)  
- статус ssh  
![part](screen/part8-3.png)  
- перенастройка службы ssh на порт 2022
![part](screen/part8-4.png)  
- перезапуск ssh для сохранения  
![part](screen/part8-5.png)  
- наличие процесса sshd  
![part](screen/part8-6.png)  
- -tan:  
- t-по протоколу TCP  
- a-Отображение всех подключений и ожидающих портов.  
- n- Отображение адресов и номеров портов в числовом формате.  
- Cтолбцы:  
- Recv-Q -количество запросов в очередях на приём на данном узле/компьютере  
- Send-Q -количество запросов в очередях на отправку на данном узле/компьютере  
- Local Address - адрес и номер локального конца сокета  
- Foreign Address - адрес и номер порта удаленного порта сокета  
- State - состояние сокета  
- Если в качестве адреса отображается 0.0.0.0 , то это означает - "любой адрес", т. е в соединении могут использоваться все IP-адреса существующие на данном компьютере.  
![part](screen/part8-7.png)  
- ps -aux | grep sshd output:  
- ps-выводит список текущих процессов на вашем сервере в виде таблицы  
- a-выбрать все процессы, кроме фоновых;  
- u-выбрать процессы пользователя.  
- x-заставляет ps перечислить все процессы, принадлежащие вам  
## Part 9  
![part](screen/part9-1.png)  
- uptime  
![part](screen/part9-2.png)  
- количество авторизованных пользователей  
![part](screen/part9-8.png)  
- общая загрузка системы  
![part](screen/part9-3.png)  
- общее количество процессов
![part](screen/part9-4.png)  
- загрузку cpu  
![part](screen/part9-5.png)  
- загрузку памяти  
![part](screen/part9-6.png)  
- pid процесса занимающего больше всего памяти  и pid процесса, занимающего больше всего процессорного времени  
![part](screen/part9-7.png)  
- отсортированно по PID  
![part](screen/part9-9.png)  
- PERCENT_CPU  
![part](screen/part9-10.png)  
- PERCENT_MEM  
![part](screen/part9-11.png)  
- TIME  
![part](screen/part9-12.png)  
- отфильтрованному для процесса sshd  
![part](screen/part9-13.png)  
- с процессом syslog, найденным, используя поиск  
![part](screen/part9-14.png)  
- с добавленным выводом hostname, clock и uptime  
![part](screen/part9-15.png)  
## Part 10  
![part](screen/part10-1.png)  
- swap раздел не активирован  
## Part 11  
![part](screen/part11-1.png)  
- размер раздела - 5492096  
- размер занятого пространства - 2673056  
- размер свободного пространства - 2519216  
- процент использования - 52%  
- единица измерения в выводе-килобайты  
![part](screen/part11-2.png)  
- размер раздела - 5.3Gb  
- размер занятого пространства - 2.6Gb  
- размер свободного пространства - 2.5Gb  
- процент использования - 52%  
- тип файловой системы для раздела - ext4  
## Part 12  
- размер папок /home, /var, /var/log (в байтах, в человекочитаемом виде)  
![part](screen/part12-1.png)  
- Выведи размер всего содержимого в /var/log (не общее, а каждого вложенного элемента, используя *)  
![part](screen/part12-2.png)   
## Part 13  
- установка утилиты  
![part](screen/part13-1.png)   
- размер папок /home   
![part](screen/part13-2.png)  
- /var   
![part](screen/part13-3.png)  
- /var/log   
![part](screen/part13-4.png)  
## Part 14  
- 1. /var/log/dmesg  
![part](screen/part14-1.png)  
- 2. /var/log/syslog  
![part](screen/part14-2.png)  
- 3. /var/log/auth.log  
![part](screen/part14-3.png)  
- перезапуск службы sshd
![part](screen/part14-4.png)  
## Part 15  
- открываем cron, через crontab -e, прописываем uptime 
![part](screen/part15-1.png)  
- каждые 2 минуты uptime  
![part](screen/part15-2.png)  
- удаляем из cron эту задачу  
![part](screen/part15-3.png)  