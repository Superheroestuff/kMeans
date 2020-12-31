#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<random>
#include<time.h>
using namespace std;

int k;

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
    //coordinates for the center of the cluster
    double x;
    double y;
    vector<Point> clusterPoints;


    bool operator!=(Cluster &c)
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

    operator =(Cluster &c)
    {
        x = c.x;
        y = c.y;
        for(int i = 0; i< c.clusterPoints.size(); i++)
        {
            this->clusterPoints.push_back(c.clusterPoints[i]);
        }
    }

    void changeCenter()
    {
        if(clusterPoints.size() == 0)
            return;

        double sumX = 0;
        double sumY = 0;
        for(int i = 0; i< clusterPoints.size(); i++)
        {
            sumX += clusterPoints[i].x;
            sumY += clusterPoints[i].y;
        }
        this->x = sumX / clusterPoints.size();
        this->y = sumY / clusterPoints.size();

        clusterPoints.clear();//clearing the cluster, because after we change the center, we start adding points from the beginning
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

void randomCentroids(Cluster c[])
{
    random_device rd;
    uniform_real_distribution<double> unif(2,10);
    default_random_engine re(rd());
    default_random_engine re2(rd());

    //for each Cluster we initialize random Center
    for(int i = 0; i<k ; i++)
    {
        c[i].x = unif(re);
        c[i].y = unif(re2);
    }
}


void setClusterToPoints(Cluster c[])
{
    for(int p = 0; p<points.size(); p++)
    {
        int setCluster = -1;
        double minDist = (double)99999;
        for(int i = 0; i<k; i++)
        {
            Point center(c[i].x,c[i].y);
            double currDist = euclidianDist(points[p], center);
            if(currDist<minDist)
            {
                minDist = currDist;
                setCluster = i;
            }
        }
        c[setCluster].clusterPoints.push_back(points[p]);
    }
}

void kMeans(Cluster c[])
{
    randomCentroids(c);
    setClusterToPoints(c);

    for(int i = 0; i<k; i++)
    {
        cout<<"Cluster "<<i<<":"<<endl;
        cout<<"Size of cluster: "<<c[i].clusterPoints.size()<<endl;
        cout<<"Coordinates of centroid of cluster: X->"<<c[i].x<<" Y->"<<c[i].y<<endl;
        cout<<endl;
    }

    while(true)
    {
        Cluster newClusters[k];
        for(int i = 0; i<k; i++)
        {
            newClusters[i]=c[i];
            newClusters[i].changeCenter();
        }
        setClusterToPoints(newClusters);
        bool isChanged = 0;
        for(int i = 0; i<k; i++)
        {
            if(newClusters[i]!=c[i])
            {
                isChanged = 1;
                break;
            }
        }

        if(isChanged == 0)
            break;

        for(int i = 0; i<k; i++)
        {
            c[i] = newClusters[i];
        }

        for(int i = 0; i<k; i++)
        {
            cout<<"Cluster "<<i<<":"<<endl;
            cout<<"Size of cluster: "<<c[i].clusterPoints.size()<<endl;
            cout<<"Coordinates of centroid of cluster: X->"<<c[i].x<<" Y->"<<c[i].y<<endl;
            cout<<endl;
        }
    }
}

int main()
{
    srand((unsigned)time(0));
    readFile("normal.txt");
    //redFile("unbalance.txt");
    cout<<"Number of Clusters K is: " ;
    cin>>k;
    Cluster c[k];
    kMeans(c);
    return 0;
}
