// RadioFileRename.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します


#include "RadioFileRenameCore.hpp"
#include "FileAction.hpp"
#include "DeleteAction.hpp"
#include "RenameAction.hpp"
#include "RecordedFile.hpp"
#include "RadioProgram.hpp"
#include "BatchWriter.hpp"
#include "ProgramProcessor.hpp"
#include "BatchWriter.hpp"
#include "Config.hpp"
#include "ProgramLoader.hpp"

//テーブルはソースコードではなく外部入力がよい

//https://docs.google.com/spreadsheets/d/1sZ2wI8POCPFSgUDddISjEbYzrwyKQnsqcH3uXLTkm2g/edit?gid=0#gid=0
RadioInfo radioInfoList[] = {

    //★★★日曜日～土曜日★★★
    {"ニッポン放送/マヂカルラブリーのオールナイトニッポン0(ZERO)",false,false,false,false,false,true,false},
    {"TBSラジオ/JUNK爆笑問題カーボーイ",false,false,false,true,false,false,false},
    {"ニッポン放送/霜降り明星のオールナイトニッポン",false,false,false,false,false,false,true},

    {"TBSラジオ/JUNKおぎやはぎのメガネびいき",false,false,false,false,false,true,false},
    {"TBSラジオ/JUNKバナナマンのバナナムーンGOLD",false,false,false,false,false,false,true},
    {"TBSラジオ/スカルプDpresents川島明のねごと",true,false,false,false,false,false,false},
    {"BAYFM78/俺のメモ帳！ontuesday",false,false,false,true,false,false,false},
    {"TOKYOFM/川島明そもそもの話",false,false,false,false,false,false,true},

    //異常終了？
    {"TBSラジオ/きしたかののブタピエロ",false,false,false,true,false,false,false},

 #if 0 //テスト中 リファクタでfalse,trueがずれた 0:日曜日
    //{"TOKYOFM/TOKYOSPEAKEASY",false,true,true,true,true,false,false},
    //{"ラジオ日本/志の輔＆雷鳥のなんでか？ニッポン",false,true,false,false,false,false,false},
    //{"ラジオ日本/真夜中のハーリー＆レイス",false,false,false,false,false,false,true},

    {"ニッポン放送/ナインティナインのオールナイトニッポン",false,false,false,false,true,false,false},
    {"ニッポン放送/オードリーのオールナイトニッポン",false,false,false,false,false,false,true},
    {"TBSラジオ/アルコ＆ピースDCGARAGE",false,false,true,false,false,false,false},
    {"ニッポン放送/高田文夫のラジオビバリー昼ズ",true,false,false,true,true,false,false},
    {"ニッポン放送/ナイツザ・ラジオショー（13時台）",true,true,true,true,false,false,false},
    {"ニッポン放送/ナイツザ・ラジオショー（14時台）",true,true,true,true,false,false,false},
    {"ニッポン放送/ナイツザ・ラジオショー（15時台）",true,true,true,true,false,false,false},
    {"ニッポン放送/中川家ザ・ラジオショー（13時台）",false,false,false,false,true,false,false},
    {"ニッポン放送/中川家ザ・ラジオショー（14時台）",false,false,false,false,true,false,false},
    {"ニッポン放送/中川家ザ・ラジオショー（15時台）",false,false,false,false,true,false,false},
    {"ニッポン放送/三四郎のオールナイトニッポン0(ZERO)",false,false,false,false,false,true,false},
    {"ニッポン放送/サンドウィッチマンザ・ラジオショーサタデー",false,false,false,false,false,true,false},


    {"TBSラジオ/JUNK伊集院光・深夜の馬鹿力",false,true,false,false,false,false,false},
    {"TBSラジオ/JUNK山里亮太の不毛な議論",false,false,false,true,false,false,false},
    {"TBSラジオ/エレ片のケツビ！",false,false,false,false,false,false,true},
    {"TBSラジオ/ガスワンプレゼンツ田中みな実あったかタイム",false,false,false,false,false,true,false},
    {"TBSラジオ/ハライチのターン！",false,false,false,false,true,false,false},
    {"TBSラジオ/空気階段の踊り場",false,true,false,false,false,false,false},
    {"TBSラジオ/土曜ワイドラジオTOKYOナイツのちゃきちゃき大放送(1)",false,false,false,false,false,true,false},
    {"TBSラジオ/土曜ワイドラジオTOKYOナイツのちゃきちゃき大放送(2)",false,false,false,false,false,true,false},
    {"TBSラジオ/ねむチキ",false,false,false,false,false,false,true},
    {"TBSラジオ/かまいたちのヘイ！タクシー！",true,false,false,false,false,false,false},
    {"TBSラジオ/スタンド・バイ・見取り図",false,false,false,true,false,false,false},

    {"文化放送/ますだおかだ岡田圭右とアンタッチャブル柴田英嗣のおかしば10時1",false,false,false,false,false,false,true},
    {"文化放送/ますだおかだ岡田圭右とアンタッチャブル柴田英嗣のおかしば11時1",false,false,false,false,false,false,true},
    {"文化放送/アインシュタイン・山崎紘菜Heat&Heart！",false,false,false,false,false,false,true},
    {"文化放送/龍角散プレゼンツ志の輔ラジオ落語DEデート",false,false,false,false,false,false,true},



    //放送終了
    //{"ニッポン放送/キン肉マン超人ラジオ",true,false,false,false,false,false,false},
    //{"ニッポン放送/アニメ『ONEPIECE』25周年記念ニッポン放送70周年記念ラ",true,false,false,false,false,false,false},

    #endif //テスト済み

    #if 0 //未テスト
    {"TBSラジオ/爆笑問題の日曜サンデー(1)",false,false,false,false,false,false,true},
    {"TBSラジオ/爆笑問題の日曜サンデー(2)",false,false,false,false,false,false,true},

    //別時間が録音されてる？    
    {"文化放送/マシンガンズの働きタイミー",false,true,false,false,false,false,false},


   #endif //未テスト
};





namespace fs = std::filesystem;


//std::string searchKeyword = "202";  //2030年以降は変更する必要がある。。。★

std::string commomDir = "C:/Users/kator/OneDrive/ドキュメント/RADIO/";    //録音ファイルが格納されているフォルダのトップ

std::string commomDirDel = "C:/f_kojin/RADIO/DEL/";    //削除するファイルが格納されるフォルダのトップ
std::string commomDirRename = "C:/f_kojin/RADIO/RENAME/";    //残すファイルが格納されるフォルダのトップ

std::string path_batchFile = "C:/Users/kator/OneDrive/ドキュメント/RADIO/move.bat";



std::vector<RadioProgram> convertToPrograms(const RadioInfo* infoList, size_t count)
{
    std::vector<RadioProgram> result;
    result.reserve(count);

    for (size_t i = 0; i < count; i++) {
        const auto& r = infoList[i];
        result.emplace_back(
            r.station_program,
            r.sun, r.mon, r.tue,
            r.wed, r.thu, r.fri, r.sat
        );
    }

    return result;
}

void RadioFileRenameCore_start()
{
    Config config;
    BatchWriter writer(path_batchFile);
    PathResolver resolver(commomDir, commomDirDel, commomDirRename);

    auto programs = ProgramLoader::loadFromRadioInfo(
        radioInfoList,
        sizeof(radioInfoList) / sizeof(RadioInfo)
    );

    for (auto& program : programs) {
        ProgramProcessor processor(program);
        processor.process(writer, resolver, config);
    }
}


