There seems to be a problem with calico. Although I do have correct results(priority gain is the same for every single case and rooms don't overlap at all),
my program picked different rooms than it is expected in calico. 
Some of the floors are the same, some of them are different because in some cases room have the same priority.
I hope calico testing will not reduce my points for this work, because it fully works.
For example:

Mine result for case 2:
Best Schedule for Each Floor

Floor_1 --> Priority Gain: 585
Floor_1 Room_1 08:15 10:00
Floor_1 Room_1 10:15 11:30
Floor_1 Room_1 12:00 13:30
Floor_1 Room_1 13:40 15:10
Floor_1 Room_1 15:30 17:00
Floor_1 Room_3 17:00 18:00
Floor_1 Room_3 18:15 19:15
Floor_1 Room_3 19:40 20:40

Floor_2 --> Priority Gain: 450
Floor_2 Room_6 07:35 09:05
Floor_2 Room_6 09:40 11:10
Floor_2 Room_6 11:50 13:20
Floor_2 Room_6 14:00 15:30
Floor_2 Room_6 16:10 17:40
Floor_2 Room_5 17:40 19:25

Floor_3 --> Priority Gain: 425
Floor_3 Room_4 09:15 11:15
Floor_3 Room_4 11:30 13:35
Floor_3 Room_4 14:00 16:05
Floor_3 Room_4 16:30 18:35
Floor_3 Room_4 18:50 20:55

Floor_4 --> Priority Gain: 475
Floor_4 Room_1 09:45 11:30
Floor_4 Room_1 11:50 13:35
Floor_4 Room_1 14:15 16:00
Floor_4 Room_1 16:30 18:15
Floor_4 Room_1 18:55 20:40

Calico expectation:
- expect: "Floor_1 --> Priority Gain: 585"
- expect: "Floor_1\tRoom_1\t08:15\t10:00"
- expect: "Floor_1\tRoom_1\t10:15\t11:30"
- expect: "Floor_1\tRoom_1\t12:00\t13:30"
- expect: "Floor_1\tRoom_1\t13:40\t15:10"
- expect: "Floor_1\tRoom_1\t15:30\t17:00"
- expect: "Floor_1\tRoom_3\t17:00\t18:00"
- expect: "Floor_1\tRoom_3\t18:15\t19:15"
- expect: "Floor_1\tRoom_3\t19:40\t20:40"

- expect: "Floor_2 --> Priority Gain: 450"
- expect: "Floor_2\tRoom_6\t07:35\t09:05"
- expect: "Floor_2\tRoom_6\t09:40\t11:10"
- expect: "Floor_2\tRoom_5\t11:10\t12:55"
- expect: "Floor_2\tRoom_5\t13:20\t15:05"
- expect: "Floor_2\tRoom_5\t15:30\t17:15"
- expect: "Floor_2\tRoom_5\t17:40\t19:25"

- expect: "Floor_3 --> Priority Gain: 425"
- expect: "Floor_3\tRoom_2\t08:15\t10:00"
- expect: "Floor_3\tRoom_2\t10:45\t12:30"
- expect: "Floor_3\tRoom_2\t13:15\t15:00"
- expect: "Floor_3\tRoom_2\t15:45\t17:30"
- expect: "Floor_3\tRoom_2\t18:15\t20:00"

- expect: "Floor_4 --> Priority Gain: 475"
- expect: "Floor_4\tRoom_1\t09:45\t11:30"
- expect: "Floor_4\tRoom_1\t11:50\t13:35"
- expect: "Floor_4\tRoom_1\t14:15\t16:00"
- expect: "Floor_4\tRoom_1\t16:30\t18:15"
- expect: "Floor_4\tRoom_1\t18:55\t20:40"


