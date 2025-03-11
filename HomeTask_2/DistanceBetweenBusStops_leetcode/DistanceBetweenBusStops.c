// Link to the solution https://leetcode.com/problems/distance-between-bus-stops/submissions/1570480387
int distanceBetweenBusStops(int *distance, int distanceSize, int start, int destination){
    if (start > destination){
        int temp = start;
        start = destination;
        destination = temp;
    }

    int clockwise = 0, total = 0;
    for (int i = 0; i < distanceSize; i++){
        if (i >= start && i < destination){
            clockwise += distance[i];
        }
        total += distance[i];
    }

    int anticlockwise = total - clockwise;
    if (clockwise < anticlockwise){
        return clockwise;
    }
    else{
        return anticlockwise;
    }
}