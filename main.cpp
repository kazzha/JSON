#include <iostream>
#include <fstream>
#include <sstream>

#pragma warning(push)
#pragma warning (disable: 26451 26495)
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#pragma warning(pop)

#include "monster.h"
#include "animation.h"

using namespace rapidjson;
using namespace std;

bool SaveToJson(const string& path, vector<Animation>& animations)
{
    StringBuffer sb; // rapidjson�� �����ϴ� �� ���� ��Ʈ�� ����. sb�� ���ڿ�
    PrettyWriter<StringBuffer> writer(sb);   // writer�ȿ� sb�� ����
    
    writer.StartObject(); // {
    writer.Key("animations");

    writer.StartArray(); // [
        for (auto animation : animations)
        {
            writer.StartObject(); 
            {
                writer.Key("name");
                writer.String(animation.GetName().c_str());
            
                writer.Key("loop");
                writer.Bool(animation.GetLoop()); 

                writer.Key("frames");
                writer.StartArray();
                for (auto frame : animation.GetFrames())
                {
                    writer.StartObject();
                    writer.Key("name"); writer.String(frame.mName.c_str());
                    writer.Key("duration"); writer.Double(frame.mDuration);
                    writer.EndObject();
                }
                writer.EndArray();
            }
            writer.EndObject();
    }
    writer.EndArray(); // ]

    writer.EndObject();  //  }

    ofstream ofs;
    ofs.exceptions(ofstream::badbit | ofstream::failbit);

    

    try
    {
        ofs.open(path);
        ofs << sb.GetString();
        ofs.close();
    }
    catch (ofstream::failure& e)
    {
        std::cerr << "invalid operation in SaveToJson()" << std::endl;
        cerr << e.what() << std::endl;
        ofs.close();
        return false;
    }

    return false;
}

bool LoadFromJson(const string& path, vector<Monster>& monsters)
{

    std::ifstream ifs;
    ifs.exceptions(ifstream::badbit | ifstream::failbit);

    stringstream ss;

    try
    {
        ifs.open(path); // ���� ��Ʈ������
        ss << ifs.rdbuf(); // �ϵ��� json ������ stringstream(���ڿ���Ʈ��)���� �Űܴ��� . rdbuf : ���� ��ü ������ ����
        string s = ss.str(); // str()�̶�� ����Լ��� �ִµ� strindstream�� string���� ��� ��ȯ����
        ifs.close();
    }
    catch (ifstream::failure e)
    {
        cerr << "invalid operation in LoadFromJson()" << std::endl;
        cerr << e.what() << endl;
        ifs.close();
        return false;
    }

    Document d;
    d.Parse(ss.str().c_str()); // ��ť��Ʈ�� �м��ؼ� �ٷ� �������
    for (auto& monObject : d["monsters"].GetArray())
    {
        Monster monster;

        monster.SetName(monObject["name"].GetString());
        Status status;
        status.mLevel = monObject["status"].GetObject()["level"].GetInt();
        status.mHP = monObject["status"].GetObject()["hp"].GetInt();
        status.mHP = monObject["status"].GetObject()["mp"].GetInt();

        monster.SetStatus(status);
        for (auto& itemObject : monObject["items"].GetArray())
        {
            Item item;
            item.mName = itemObject["name"].GetString();
            item.mGold = itemObject["gold"].GetInt();
            monster.AddDropItem(item);
        }
        monsters.push_back(monster);
    }

   // cout << d["monsters"].GetArray()[0].GetObject()["name"].GetString() << endl; //�迭�� 0��°���� Ű�� name�� ��Ʈ���� ������
    return true;
}
int main()
{
    std::vector<Animation> animations;

    Animation a;
    a.SetName("Move");
    a.SetLoop(true);
    a.AddFrame({ "bug1_1.png", 0.3 });
    a.AddFrame({ "bug1_2.png", 0.3 });
    a.AddFrame({ "bug1_3.png", 0.3 });
    a.AddFrame({ "bug1_4.png", 0.3 });
    animations.push_back(a);

    a.GetFrames().clear();
    a.SetName("Die");
    a.SetLoop(false);
    a.AddFrame({ "bug1_die.png", 0.2 });
    a.AddFrame({ "die01.png", 0.2 });
    a.AddFrame({ "die02.png", 0.2 });
    a.AddFrame({ "die03.png", 0.2 });
    a.AddFrame({ "die04.png", 0.2 });
    a.AddFrame({ "die05.png", 0.2 });
    a.AddFrame({ "die06.png", 0.2 });
    a.AddFrame({ "die07.png", 0.2 });
    a.AddFrame({ "die08.png", 0.2 });
    a.AddFrame({ "die09.png", 0.2 });
    a.AddFrame({ "die10.png", 0.2 });
    animations.push_back(a);

    SaveToJson("Data/BugAnimation.json", animations);

}