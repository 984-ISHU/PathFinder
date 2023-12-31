#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define INF 9999
#define MAX_STATIONS 15

// Structure to represent a railway station.
struct Station {
    char name[100];
    int id;
};

// Function prototypes.
void strtrim(char *str);
void initStation(struct Station* station, const char* name, const int id);
int minDistance(int distance[], bool visited[], int numStations);
void printPath(int parent[], int j, const char* stations[]);
void dijkstra(int graph[MAX_STATIONS][MAX_STATIONS], int numStations, int src, int dest, const char* stations[]);
void pathFinder(char sourceName[], char destinationName[]);


int main() {
    printf("Welcome to PathFinder!!\n");

    char sourceName[100];
    char destinationName[100];

    while (true) {
        printf("-------------------------------------------------------\n");
        printf("\nEnter the source station: ");
        fgets(sourceName, sizeof(sourceName), stdin);
        sourceName[strcspn(sourceName, "\n")] = '\0';
        strtrim(sourceName);

        printf("Enter the destination station: ");
        fgets(destinationName, sizeof(destinationName), stdin);
        destinationName[strcspn(destinationName, "\n")] = '\0';
        strtrim(destinationName);

        pathFinder(sourceName, destinationName);

        int choice = 0;
        printf("\n0.Exit  1.Continue>>> ");
        scanf("%d", &choice);

        if (choice != 1) {
            break;
        }

        getchar();
    }

    return 0;
}

// Function to remove leading and trailing spaces
void strtrim(char *str) {
    // Remove leading whitespaces
    while (isspace(*str)) {
        ++str;
    }

    // Remove trailing whitespaces
    char *end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) {
        --end;
    }

    // Null-terminate the trimmed string
    *(end + 1) = '\0';
}

// Function to initialize a station
void initStation(struct Station* station, const char* name, const int id) {
    strcpy(station->name, name);
    station->id = id;
}

// Function to find the station with the minimum distance value
int minDistance(int distance[], bool visited[], int numStations) {
    int min = INF;
    int minIndex;

    for (int v = 0; v < numStations; v++) {
        // Check if the station has not been visited and has a distance less than or equal to the current minimum
        if (!visited[v] && distance[v] <= min) {
            min = distance[v];  // Update the minimum distance
            minIndex = v;       // Update the index of the station with the minimum distance
        }
    }

    return minIndex;  // Return the index of the station with the minimum distance
}


// Function to print the shortest path from source to destination
void printPath(int parent[], int j, const char* stations[]) {
    // Base case
    if (parent[j] == -1) {
        printf("%s", stations[j]);
        return;
    }

    printPath(parent, parent[j], stations); // Using Recurrsion
    printf(" -> %s", stations[j]);
}

// Function to find the minimum distance between two stations using Dijkstra's algorithm
void dijkstra(int graph[MAX_STATIONS][MAX_STATIONS], int numStations, int src, int dest, const char* stations[]) {
    int distance[MAX_STATIONS];
    bool sptSet[MAX_STATIONS];
    int parent[MAX_STATIONS];

    // Initialize arrays for distance, visited status, and parent
    for (int i = 0; i < numStations; i++) {
        distance[i] = INF;   // Set all distances to infinity initially
        sptSet[i] = false;   // Mark all stations as not visited
        parent[i] = -1;      // Set parent of all stations to -1 initially
    }

    distance[src] = 0;  // Set the distance of the source station to 0

    // Iterate through all stations
    for (int count = 0; count < numStations - 1; count++) {
        int u = minDistance(distance, sptSet, numStations);  // Find the station with the minimum distance
        sptSet[u] = true;  // Mark the selected station as visited

        // Update distances of the neighboring stations of the selected station
        for (int v = 0; v < numStations; v++) {
            if (!sptSet[v] && graph[u][v] && distance[u] != INF && (distance[u] + graph[u][v] < distance[v])) {
                distance[v] = distance[u] + graph[u][v];  // Update the distance
                parent[v] = u;  // Set the parent of the neighboring station
            }
        }
    }

    // Print the shortest distance and path
    printf("\nShortest Distance from %s to %s: %d km\n", stations[src], stations[dest], distance[dest]);
    printf("Shortest Path: ");
    printPath(parent, dest, stations);
    printf("\n");
}

void pathFinder(char sourceName[],char destinationName[]){
    int numStations = 15;
    struct Station stations[MAX_STATIONS];
    const char* stationNames[MAX_STATIONS] = {"Belgaum", "Hubli", "Hospet", "Dharmavaram", "Chikjajur", "Birur", "Mangalore", "Hassan", "Bangalore", "Mysore", "Jolarpettai", "Dharmavaram", "Wadi", "Miraj", "Vasco da gama"};

    // Initialize station names.
    for (int i = 0; i < numStations; i++) {
        initStation(&stations[i], stationNames[i], i);
    }
    
    // Adjacency Matrix.
    int graph[MAX_STATIONS][MAX_STATIONS] = {
        {0, 142, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 123, INF},
        {142, 0, 142, INF, 190, INF, INF, INF, INF, INF, INF, INF, 477, INF, INF},
        {INF, 142, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, 0, INF, INF, INF, INF, 190, INF, INF, INF, INF, INF, INF},
        {INF, 190, INF, INF, 0, 68, INF, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, INF, 68, 0, INF, 93, 211, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, 0, 188, INF, INF, INF, INF, INF, INF, 337},
        {INF, INF, INF, INF, INF, 93, 188, 0, 179, 121, INF, INF, INF, INF, INF},
        {INF, INF, INF, 190, INF, 211, INF, 179, 0, 137, 148, 175, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, 121, 137, 0, INF, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, 148, INF, 0, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, INF, INF, 175, INF, INF, 0, INF, INF, INF},
        {INF, 477, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, INF, INF},
        {123, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, INF},
        {INF, INF, INF, INF, INF, INF, 337, INF, INF, INF, INF, INF, INF, INF, 0},

    };
    
    int source = -1, destination = -1;

    // Find the indices corresponding to the entered station names.
    for (int i = 0; i < numStations; i++) {
        if (strcasecmp(sourceName, stationNames[i]) == 0) {
            source = i;
        }
        if (strcasecmp(destinationName, stationNames[i]) == 0) {
            destination = i;
        }
    }

    if (source != -1 && destination != -1) {
        dijkstra(graph, numStations, source, destination, stationNames);
    } else {
        printf("Source or destination station not found in the list.\n");
    }
}
