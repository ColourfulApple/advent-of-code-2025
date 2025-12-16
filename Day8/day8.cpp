#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <array>
#include <sstream>
#include <cmath>
#include <limits>
#include <algorithm>
#include <set>

struct junctionBox
{
    int pos_x;
    int pos_y;
    int pos_z;
    
    bool connected;

    bool operator== (const junctionBox other) const
    {
        return (pos_x == other.pos_x && pos_y == other.pos_y && pos_z == other.pos_z);
    }

    bool operator<(const junctionBox other) const 
    {
        if (pos_x != other.pos_x) return pos_x < other.pos_x;
        if (pos_y != other.pos_y) return pos_y < other.pos_y;
        return pos_z < other.pos_z;
    }

    junctionBox(){};

    junctionBox(int x, int y, int z) : pos_x(x), pos_y(y), pos_z(z), connected(false) {}

    junctionBox(int posArr[3]) : pos_x(posArr[0]), pos_y(posArr[1]), pos_z(posArr[2]) {}
};

struct Edge
{
    junctionBox *boxA;
    junctionBox *boxB;

    double distance;

    bool operator<(const Edge& other) const 
    {
        return distance < other.distance;
    }
};

double calculateDistance(junctionBox& boxA, junctionBox& boxB);

int main()
{
    std::ifstream inputFile("input.txt");

    std::vector<junctionBox> jBoxVector;
    std::string line;

    //Reading junction box into jBoxVector
    int i = 0;
    while(std::getline(inputFile, line))
    {
        int posArr[3];
        std::stringstream line_ss(line);
        std::string pos_str;

        for(int i = 0; std::getline(line_ss, pos_str, ',');i++)
        {
            posArr[i] = std::stoi(pos_str);
        }
        jBoxVector.push_back(junctionBox(posArr));
    }

    std::vector<Edge> distance_vector;
    //calculate all distances between junction box;
    for (size_t i = 0; i < jBoxVector.size(); i++)
    {
        for (size_t j = i + 1; j < jBoxVector.size(); j++)
        {
            Edge temp;
            temp.boxA = &jBoxVector[i];
            temp.boxB = &jBoxVector[j];
            temp.distance = calculateDistance(*temp.boxA, *temp.boxB);
            distance_vector.push_back(temp);
        }
    }

    std::sort(distance_vector.begin(), distance_vector.end());

    std::vector<std::set<junctionBox>> junction_circuit;
    int z = 0;
    junctionBox* prevA;
    junctionBox* prevB;
    for (Edge& e: distance_vector) 
    {
        if(e.boxA->connected == true && e.boxB->connected == true) 
        {
            for(auto i = 0; i < junction_circuit.size(); i++)
            {
                if(junction_circuit[i].find(*e.boxA) != junction_circuit[i].end())
                {
                    for(auto j = 0; j < junction_circuit.size(); j++)
                    {
                        if(junction_circuit[j].find(*e.boxB) != junction_circuit[j].end()) 
                        {
                            if(i == j)
                            {
                                break;
                            }
                            junction_circuit[j].insert(junction_circuit[i].begin(), junction_circuit[i].end());
                            junction_circuit.erase(junction_circuit.begin() + i);
                            break;
                        }
                    }
                    break;
                }
            }
        }
        else if(e.boxA->connected == true) 
        {
            for(auto& set : junction_circuit)
            {
                if(set.find(*e.boxA) != set.end())
                {
                    set.insert(*e.boxB);
                    e.boxB->connected = true;
                    break;
                }
            }
        }
        else if(e.boxB->connected == true)
        {
            for(auto& set : junction_circuit)
            {
                if(set.find(*e.boxB) != set.end())
                {
                    set.insert(*e.boxA);
                    e.boxA->connected = true;
                    break;
                }
            }
        }
        else
        {
            junction_circuit.push_back({*e.boxA, *e.boxB});
            e.boxA->connected = true;
            e.boxB->connected = true;
        }
        prevA = e.boxA;
        prevB = e.boxB;
        if(junction_circuit[0].size() == 1000)
        {
            break;
        }
    }

    std::sort(junction_circuit.begin(), junction_circuit.end(), [](const std::set<junctionBox> a, std::set<junctionBox> other)
{
    return a.size() > other.size();
});

    long long ans = (long long)prevA->pos_x * prevB->pos_x;
    std::cout << "last two: " << ans;

}


double calculateDistance(junctionBox& boxA, junctionBox& boxB)
{
    double dx = boxA.pos_x - boxB.pos_x;
    double dy = boxA.pos_y - boxB.pos_y;
    double dz = boxA.pos_z - boxB.pos_z;
    double distance = std::hypot(dx, dy, dz);
    return distance;
}