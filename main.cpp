#include <iostream>
#include<iostream>
#include<fstream>
#include <stdexcept>
#include <string>
#include <stdlib.h>
#include <list>
#include <vector>
#include <map>
#include<iostream>
#include <list>
#include <sstream>
#include<set> // for set operations

using namespace std;

void loadInputStream(string &filename, ifstream &stream){
    stream.open(filename.c_str());
    if(!stream){
        cerr << "cannot open" << /*stream*/ filename << " for reading" << endl;
        exit(0);
    }
}

vector<string> lineToItemsSplit(string &line, char &delimiter){
    vector<string> rtnList;
    size_t pos = 0;
    string token;

    if (!line.empty() && line[line.size() - 1] == '\r')
        line.erase(line.size() - 1);

    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        rtnList.push_back(token);
        line.erase(0, pos + 1);
    }
    rtnList.push_back(line);
    return rtnList;
}

class SegmentMap{

    map<string, vector<string>> map_of_segments;

    public:
        SegmentMap(ifstream &input_file) {
            string line;
            char delimiter = ' ';
            int i = 0;

            while(getline(input_file, line)){
                vector<string> data = lineToItemsSplit(line, delimiter);
                string campaignName = data[0];
                cout << "CampaignName :: " << campaignName << endl;
                for (i=1; i < data.size(); i++) {
                    addCampaign(data[i], campaignName);
                    cout << "Segment :: " << data[i] << '\t';
                }
                cout << endl;
            }
        }

        vector<string> getCampaigns (const string &segment){
            return map_of_segments[segment];
        }

        void findCampaign(vector<string> segments){
        }

        vector<string> addCampaign (const string &segment, const string &campaign){
            vector<string> my_segment = getCampaigns(segment);
            my_segment.push_back(campaign);
            map_of_segments[segment] = my_segment;
            return map_of_segments[segment];
        }

        void displaySegmentMap(){
            cout << "***DISPLAY***"<< endl;
            for (auto segment_it = map_of_segments.begin(); segment_it != map_of_segments.end(); segment_it++)
            {
                cout << "Segment: " << segment_it->first << endl;
                for(auto campaign_it = segment_it->second.begin(); campaign_it != segment_it->second.end(); ++campaign_it) {
                    cout << "Campaign: " << *campaign_it << "\t";
                }
                cout << endl;
            }
            cout << "------------"<< endl;

        }
};

// Driver program
int main()
{
    string file_path = R"(C:\Users\shrey\CLionProjects\CampaignProject\file1.txt)";
    ifstream fileStream;
    string line;
    loadInputStream(file_path, fileStream);

    SegmentMap s1 = SegmentMap(fileStream);
    s1.displaySegmentMap();
    return 0;
}