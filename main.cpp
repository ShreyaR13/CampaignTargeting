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
        cerr << "Cannot open " << filename << " for reading" << endl;
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

    public:
    map<string, vector<string>> map_of_segments;
    map<string, size_t> map_of_campaign_hits;
    char delimiter = ' ';

    SegmentMap(ifstream &input_file) {
        string line;
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

    vector<string> findCountCampaignNames(const map<string, size_t> mapObj, const size_t count){
        vector<string> rtnCampaigns;
        for (auto camp = mapObj.begin(); camp != mapObj.end(); camp++) {
            if(camp->second == count){
                rtnCampaigns.push_back(camp->first);
            }
        }
        return rtnCampaigns;
    }

    void findCampaign(vector<string> &segments) {
        vector<string> all_campaign = getMergedCampaigns(segments);
        set<string> distinct_campaign;
        map<string, size_t> count_campaign;

        for (auto &camp : all_campaign) {
            distinct_campaign.insert(camp);
        }
        for (auto &camp : distinct_campaign) {
            count_campaign[camp] = 0;
        }
        for (auto &camp : all_campaign) {
            count_campaign[camp] = ++count_campaign[camp];
        }

//        for (auto camp = count_campaign.begin(); camp != count_campaign.end(); camp++) {
//            cout << "Campaign: " << camp->first << "\t Count: " << camp->second << endl;
//        }
        size_t number_of_campaign = distinct_campaign.size();
        set<size_t> distinct_count;

        for (auto camp = count_campaign.begin(); camp != count_campaign.end(); camp++) {
            distinct_count.insert(camp->second);
        }
        size_t max_count = *max_element(distinct_count.begin(), distinct_count.end());
        vector<string> max_Campaigns = findCountCampaignNames(count_campaign, max_count);
        string campaign_name;

        if(max_Campaigns.size()>1){
            // This Extra Point Case
            count_campaign.clear();
            for (auto &camp : max_Campaigns) {
                count_campaign[camp] = map_of_campaign_hits[camp];
            }
            distinct_count.clear();

            for (auto camp = count_campaign.begin(); camp != count_campaign.end(); camp++) {
                distinct_count.insert(camp->second);
            }
            size_t min_count = *min_element(distinct_count.begin(), distinct_count.end());
            vector<string> min_Campaigns = findCountCampaignNames(count_campaign, min_count);

            if(min_Campaigns.size()==1){
                cout << "#################" << min_Campaigns.front() << "---------" << endl;
            }else if(min_Campaigns.size()>1){
                int rand_index = rand() % (int) min_Campaigns.size();
                cout << "#################" << min_Campaigns[rand_index] << "---------" << endl;
            }

        }else if(max_Campaigns.size() == 1){
            cout << "#################" << max_Campaigns.front() << "---------" << endl;
        } else{
            cout << "#################No Campaigns---------" << endl;
        }
        map_of_campaign_hits[campaign_name] = ++map_of_campaign_hits[campaign_name];
    }

    vector<string> addCampaign(const string &segment, const string &campaign) {
        vector<string> my_campaign = getCampaigns(segment);
        my_campaign.push_back(campaign);
        map_of_campaign_hits[campaign] = 0; // Init hit count
        map_of_segments[segment] = my_campaign;
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
int main(int argc, char** argv)  {
    ifstream fileStream;
    string line;
    string file_path;

//    cout << "rand() % max_rand; " << rand() % 2 << endl;
//    cout << "rand() % max_rand; " << rand() % 2 << endl;
//    cout << "rand() % max_rand; " << rand() % 2 << endl;
//    cout << "rand() % max_rand; " << rand() % 2 << endl;
//    return 0;

    if(argc < 2){
        cout << "Please pass in Data input file! (Eg. Campaign.txt)" << endl;
        return 0;
    }

    file_path = argv[1];
    loadInputStream(file_path, fileStream);
    SegmentMap segmentMapObj = SegmentMap(fileStream);

    while(line != "n"){
        cout << "Enter input to find the campaign or 'n' to exit: " << endl;
        getline (cin, line);
        if (line != "n") {
            vector<string> segments = lineToItemsSplit(line, segmentMapObj.delimiter);

            //vector<string> segments = {"1025"};
            segmentMapObj.findCampaign(segments);

        }else{
            break;
        }
    }
    return 0;
}