#include <iostream>
#include<fstream>
#include <stdlib.h>
#include <list>
#include <vector>
#include <map>
#include<set> // for set operations
#include <algorithm>

using namespace std;

void loadInputStream(string &filename, ifstream &stream) {
    stream.open(filename.c_str());
    if (!stream) {
        cerr << "cannot open" << /*stream*/ filename << " for reading" << endl;
        exit(0);
    }
}

vector<string> lineToItemsSplit(string &line, char &delimiter) {
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

class SegmentMap {

    map<string, vector<string>> map_of_segments;
    map<string, int> map_of_campaign_hits;

public:
    SegmentMap(ifstream &input_file) {
        string line;
        char delimiter = ' ';
        int i = 0;

        while (getline(input_file, line)) {
            vector<string> data = lineToItemsSplit(line, delimiter);
            string campaignName = data[0];
            for (i = 1; i < data.size(); i++) {
                addCampaign(data[i], campaignName);
            }
        }
    }

    vector<string> getCampaigns(const string &segment) {
        return map_of_segments[segment];
    }

    vector<string> getMergedCampaigns(const vector<string> &segments) {
        vector<string> rtnCampaigns;
        vector<string> tmp_campaign;
        for (auto seg : segments) {
            tmp_campaign = getCampaigns(seg);
            for (auto camp : tmp_campaign) {
                rtnCampaigns.push_back(camp);
            }
        }
        return rtnCampaigns;
    }

    void findCampaign(vector<string> segments) {
        vector<string> all_campaign = getMergedCampaigns(segments);
        set<string> distinct_campaign;
        map<string, size_t> count_campaign;

        for (auto camp : all_campaign) {
            distinct_campaign.insert(camp);
        }
        for (auto camp : distinct_campaign) {
            count_campaign[camp] = 0;
        }
        for (auto camp : all_campaign) {
            count_campaign[camp] = ++count_campaign[camp];
        }

        for (auto camp = count_campaign.begin(); camp != count_campaign.end(); camp++) {
            cout << "Campaign: " << camp->first << "\t Count: " << camp->second << endl;
        }
        size_t number_of_campaign = distinct_campaign.size();
        set<size_t> distinct_count;

        for (auto camp = count_campaign.begin(); camp != count_campaign.end(); camp++) {
            distinct_count.insert(camp->second);
        }

        size_t max_count = 0;
        string campaign_name = "";

        if(number_of_campaign > distinct_count.size()){
            // This Extra Point Case
        }else{
            for (auto camp = count_campaign.begin(); camp != count_campaign.end(); camp++) {
                if(camp->second > max_count){
                    max_count = camp->second;
                    campaign_name = camp->first;
                }
            }
        }

        map_of_campaign_hits[campaign_name] = ++map_of_campaign_hits[campaign_name];
        cout << "campaign_name: " << campaign_name << " max_count: " << max_count << endl;
    }

    vector<string> addCampaign(const string &segment, const string &campaign) {
        vector<string> my_segment = getCampaigns(segment);
        my_segment.push_back(campaign);
        map_of_campaign_hits[campaign] = 0; // Init hit count
        map_of_segments[segment] = my_segment;
        return map_of_segments[segment];
    }

    void displaySegmentMap() {
        cout << "***DISPLAY***" << endl;
        for (auto segment_it = map_of_segments.begin(); segment_it != map_of_segments.end(); segment_it++) {
            cout << "Segment: " << segment_it->first << endl;
            for (auto campaign_it = segment_it->second.begin();
                 campaign_it != segment_it->second.end(); ++campaign_it) {
                cout << *campaign_it << "\t";
            }
            cout << endl;
        }
        cout << "------------" << endl;

    }
};

// Driver program
int main() {
    string file_path = R"(C:\Users\shrey\CLionProjects\CampaignProject\file1.txt)";
    ifstream fileStream;
    string line;
    loadInputStream(file_path, fileStream);
    SegmentMap s1 = SegmentMap(fileStream);
//    s1.displaySegmentMap();
    vector<string> segments = {"10"};
    s1.findCampaign(segments);
    return 0;
}