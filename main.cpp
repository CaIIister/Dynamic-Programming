/**
 * BLG 336E - Analysis of Algorithms II
 * Assignment 3
 * Taras Demchyna
 * 912310109
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

/* YOU CAN INCLUDE ANY OTHER NECESSARY LIBRARIES */


/* YOU CAN DEFINE EXTRA FUNCTIONS AND MODIFY THE CODE TEMPLATE */

/* YOU HAVE TO CONSIDER THE OUTPUT FORMAT TO TEST YOUR CODE WITH CALICO */

using namespace std;

struct TimeIntervals
{
    string startTime;
    string finishTime;
};

struct Room
{
    string floorName;
    string roomNumber;
    int priority;
    TimeIntervals interval;

    Room()
    {
	    
    }
    Room(string floor, string room, int prior, string startTime, string finishTime)
	{
        floorName = floor;
        roomNumber = room;
        priority = prior;
        interval.startTime = startTime;
        interval.finishTime = finishTime;
    }

    bool operator<(const Room& other) const
	{
        return interval.startTime < other.interval.startTime;
    }
};

struct Item
{
    // YOUR CODE HERE
    string name;
    double value;
    double price;
};

/* START: WEIGHTED INTERVAL SCHEDULING (for each floor) */
struct Schedule
{
    // YOUR CODE HERE
    string floorNumber;
    vector<Room> rooms;
    vector<int> previousIntervals;
    vector<int> optimalRooms;
    vector<Room> scheduleOPT;

    Schedule(string floor, vector<Room> initialRooms)
	{
        floorNumber = floor;
        rooms = initialRooms;
    }
    Schedule()
    {
	    
    }
    /*This method helps to find room schedule with the biggest index,
	which finish time less or equal than start time of particular room schedule*/
    vector<int> matchInterval()
	{
        vector<int> result;
        vector<int> start, finish;
        for (const Room& room : rooms) 
        {
            start.push_back(parseTime(room.interval.startTime));
            finish.push_back(parseTime(room.interval.finishTime));
        }
        for (size_t i = 0; i < rooms.size(); i++) 
        {
            auto iter = lower_bound(finish.begin(), finish.end(), start[i] + 1);
            int index = distance(finish.begin(), iter) - 1;
            result.push_back(index);
        }
        return result;
    }
    //This recursive method finds maximum weight for particular room
    int optimal(int i)
	{
        if (i == -1) 
        {
            return 0;
        }
        else if (static_cast<size_t>(i) < optimalRooms.size()) 
        {
            return optimalRooms[i];
        }
        else 
        {
            return max(rooms[i].priority + optimal(previousIntervals[i]), optimal(i - 1));
        }
    }
    //This method finds optimal weight for each room
    void weightedIntervals()
	{
        for (size_t i = 0; i < rooms.size(); i++)
        {
            int optimal_i = optimal(i);
            optimalRooms.push_back(optimal_i);
        }
        Scheduling(rooms.size() - 1);
    }
    //This method finds subset of rooms that fit the criteria
    void Scheduling(int i)
	{
        if (i > -1) {
            if (rooms[i].priority + optimal(previousIntervals[i]) >= optimal(i - 1))
            {
                scheduleOPT.push_back(rooms[i]);
                Scheduling(previousIntervals[i]);
            }
            else 
            {
                Scheduling(i - 1);
            }
        }
    }
    //Method for changing time from string to int
    int parseTime(string time)
	{
        int item1 = stoi(time.substr(0, 2));
        int item2 = stoi(time.substr(3, 2));
        int result = item1 * 60 + item2;
        return result;
    }
    //Method for calculating priority gain for specific set of rooms
    int priorityGain()
	{
        int result = 0;
        for (const Room& room : rooms) 
        {
            result += room.priority;
        }
        return result;
    }
};
//Helper method for getting set of rooms in reverse order
vector<Room> reverseRooms(vector<Room> rooms)
{
    vector<Room> result;
    for (int i = rooms.size() - 1; i >= 0; i--) 
    {
        result.push_back(rooms[i]);
    }
    return result;
}
// function to find the best schedule for each floor
vector<Schedule> weighted_interval_scheduling(vector<Schedule> schedules)
{
    // YOUR CODE HERE
    vector<Schedule> optimal_schedules;
    for (Schedule& schedule : schedules) 
    {
        sort(schedule.rooms.begin(), schedule.rooms.end());
        schedule.previousIntervals = schedule.matchInterval();
        schedule.weightedIntervals();
        schedule.scheduleOPT = reverseRooms(schedule.scheduleOPT);
        Schedule temp;
        temp.floorNumber = schedule.floorNumber;
        temp.rooms = schedule.scheduleOPT;
        optimal_schedules.push_back(temp);
    }
    return optimal_schedules;
}
//Method for reading priority of rooms from file
vector<Room> readPriorityFile(const string& filename)
{
    vector<Room> priorities;
    ifstream file(filename);
    if (!file.is_open()) 
    {
        cerr << "Error opening file: " << filename << endl;
        return priorities;
    }
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        Room room;
        ss >> room.floorName >> room.roomNumber >> room.priority;
        priorities.push_back(room);
    }
    file.close();
    return priorities;
}
//Method for reading time intervals from file
vector<Room> readTimeIntervalFile(const string& filename)
{
    vector<Room> rooms;
    ifstream file(filename);
    if (!file.is_open()) 
    {
        cerr << "Error opening file: " << filename << endl;
        return rooms;
    }
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) 
    {
        stringstream ss(line);
        Room room;
        ss >> room.floorName >> room.roomNumber >> room.interval.startTime >> room.interval.finishTime;
        rooms.push_back(room);
    }
    file.close();
    return rooms;
}
//Method for merging information from both priority and time interval files
vector<Room> mergeRooms(vector<Room> roomsPriority, vector<Room> roomsInterval)
{
    int j = 0;
    int r = 0;
    vector<Room> result;
    for (size_t i = 0; i < roomsInterval.size(); i++)
    {
        if (roomsPriority[j].roomNumber != roomsInterval[i].roomNumber)
        {
            j++;
        }
        result.push_back(roomsInterval[i]);
        result[r++].priority = roomsPriority[j].priority;
    }
    return result;
}
//Method for transforming set of rooms into set of schedules(for each floor)
vector<Schedule> transformation(vector<Room> roomsSchedule)
{
    size_t n = 0;
    vector<Schedule> result;
    result.push_back(Schedule());
    result[0].floorNumber = roomsSchedule[0].floorName;
    for (size_t i = 0; i < roomsSchedule.size(); i++) 
    {
        if (roomsSchedule[i].floorName != result[n].floorNumber)
        {
            n++;
            result.push_back(Schedule());
            result[n].floorNumber = roomsSchedule[i].floorName;
        }
        result[n].rooms.push_back(roomsSchedule[i]);
    }
    return result;
}

// *** END ***


/* START: KNAPSACK (for items) */


// Function to select the most valuable items that can be purchased with a certain budget
vector<Item> knapsack(const vector<Item>& Items, int budget)
{
    vector<vector<double>> itemsPrice(Items.size() + 1, vector<double>(budget + 1, 0));

    for (size_t i = 1; i <= Items.size(); i++) 
    {
        int price = Items[i - 1].price;
        double value = Items[i - 1].value;

        for (int j = 1; j <= budget; j++) {
            itemsPrice[i][j] = itemsPrice[i - 1][j];

            if (j >= price && itemsPrice[i - 1][j - price] + value > itemsPrice[i][j]) 
            {
                itemsPrice[i][j] = itemsPrice[i - 1][j - price] + value;
            }
        }
    }

    double money = budget;
    vector<Item> selected_items;

    for (size_t i = Items.size(); i > 0 && money > 0; i--) 
    {
        if (itemsPrice[i][money] != itemsPrice[i - 1][money]) 
        {
            selected_items.push_back(Items[i - 1]);
            money -= Items[i - 1].price;
        }
    }

    return selected_items;
}
//Method for calculating total value of items in knapsack
double totalValue(vector<Item> items)
{
    double result = 0.0;
    for (const Item& item : items) 
    {
        result += item.value;
    }
    result = round(result * 10) / 10;
    return result;
}
//Method for reading items from file
vector<Item> readItemFile(const string& filename)
{
    vector<Item> items;
    ifstream file(filename);
    if (!file.is_open()) 
    {
        cerr << "Error opening file: " << filename << endl;
        return items;
    }
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        Item item;
        ss >> item.name >> item.price >> item.value;
        items.push_back(item);
    }
    file.close();
    return items;
}
//Method for printing schedule
void printFloor(Schedule schedule)
{
    cout << "\n\n" << schedule.floorNumber << " --> Priority Gain: " << schedule.priorityGain();
    for (size_t j = 0; j < schedule.rooms.size(); j++) 
    {
        cout << "\n" << schedule.rooms[j].floorName
            << " " << schedule.rooms[j].roomNumber
            << " " << schedule.rooms[j].interval.startTime
            << " " << schedule.rooms[j].interval.finishTime;
    }
}
//Method for printing Items in knapsack
void printItems(vector<Item> items)
{
    cout << "\n\nBest Use of Budget" << "\nTotal Value --> " << totalValue(items) << "\n\n";
    for (const Item& item : items) 
    {
        cout << item.name << "\n";
    }
}

// *** END ***

int main(int argc, char* argv[])
{
    string case_no = argv[1];
    string case_name = "case_" + case_no;
    string path = "./inputs/" + case_name;
    vector<Room> priorities = readPriorityFile(path + "/priority.txt");
    vector<Room> timeIntervals = readTimeIntervalFile(path + "/room_time_intervals.txt");
    vector<Item> items = readItemFile(path + "/items.txt");
    int total_budget = 200000;

    // YOUR CODE HERE

    // Merge priorities and time intervals, transform schedules, and find best scheduling
    vector<Room> mergedRooms = mergeRooms(priorities, timeIntervals);
    vector<Schedule> schedules = transformation(mergedRooms);
    vector<Schedule> bestScheduling = weighted_interval_scheduling(schedules);
    vector<Item> chosenItems = knapsack(items, total_budget);

    // Output the results
    cout << "Best Schedule for Each Floor";
    for (size_t i = 0; i < bestScheduling.size(); i++) {
        printFloor(bestScheduling[i]);
    }
    printItems(chosenItems);
    cout << "_EOF_";

    return 0;
}
