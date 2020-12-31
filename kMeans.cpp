#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
using namespace std;

struct Point
{
    double x;
    double y;

    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
};

vector<Point> points;

double euclidianDist(const Point &A, const Point &B)
{
    double x = A.x - B.x;
    double y = A.y - B.y;
    return sqrt(pow(x,2) + pow(y,2));
}

struct Cluster
{
    //coord for the center of the cluster
    double x;
    double y;
    vector<Point> clusterPoints;


    bool isChanged(Cluster &c)
    {
        if(clusterPoints.size() != c.clusterPoints.size())
            return 1;

        for(int i = 0; i<clusterPoints.size(); i++)
        {
            if((clusterPoints[i].x != c.clusterPoints[i].x) || (clusterPoints[i].y != c.clusterPoints[i].y))
                return 1;
        }
        return 0;
    }

    void printCenterOfCluster()
    {
        cout<<"Center of Cluster: "<<x<<" "<<y<<endl;
    }
};

void readFile(const char* fileName)
{
    ifstream file;
    file.open(fileName);
    if(!file.is_open())
    {
        cout<<"File did not opened!"<<endl;
        return;
    }

    char c;
    string number;
    double x,y;
    while(file.get(c))
    {
        number += c;
        if(c == '\t')
        {
            x = stod(number);
            number = "";
        }
        if(c == '\n')
        {
            y = stod(number);
            number = "";
            Point p = Point(x,y);
            points.push_back(p);

        }
    }
}


int main()
{
    readFile("normal.txt");
    //redFile("unbalance.txt");
    cout<<points[2].x<<" "<<points[2].y<<endl;
    return 0;
}
