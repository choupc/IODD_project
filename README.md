IODD_project
============

mp3 player(mplayer) and 7_segment LCD on TQ2440



slave mode
============

運行mplayer -slave -quiet <mp3>，並在控制台視窗輸入slave指令。 //-slave:啟動從模式，-quiet:不輸出冗餘的資訊

常用到的 Mplayer slave指令：

loadfile   string        //參數string 為 歌曲名字。 

volume 100 1//設置音量 中間的為音量的大小。

mute1/0//靜音開關

pause//暫停/取消暫停

get_time_length//返回值是播放檔的長度，以秒為單位。

seek value  //向前查找到檔的位置播放 參數value為秒數。

get_percent_pos//返回文件的百分比（0--100）

get_time_pos//列印出在檔的當前位置用秒表示，採用浮點數

volume <value> [abs] //增大/減小音量，或將其設置為<value>，如果[abs]不為零

get_file_name//列印出當前檔案名

get_meta_album//列印出當前檔的'專輯'的中繼資料

get_meta_artist//列印出當前檔的'藝術家'的中繼資料

get_meta_comment//列印出當前檔的'評論'的中繼資料

get_meta_genre//列印出當前檔的'流派'的中繼資料

get_meta_title//列印出當前檔的'標題'的中繼資料

get_meta_year//列印出當前檔的'年份'的中繼資料
