 #include "cprocessdata.h"

CprocessData::CprocessData()
{
}


/**
 * 将文本数据存入到Map中，产生事务数据库D，即textDataBase
 **/
int CprocessData::ReadFile()
{
    FILE *ReadFile;
    FILE *ReadFile2;
    QString dataFileName1 = "go_track_trackspoints.csv";
    QString dataFileName2 = "go_track_tracks.csv";


    int i32LineIndex = 0;

    /*打开文本文件*/
    ReadFile = fopen(dataFileName1.toLatin1().data(), "r");
    if(ReadFile == NULL){
        qDebug()<<"OpenFile ERROR";
        return EXIT_FAILURE;
    }


    ReadFile2 = fopen(dataFileName2.toLatin1().data(), "r");
    if(ReadFile2 == NULL){
        qDebug()<<"OpenFile ERROR";
        return EXIT_FAILURE;
    }



    while(!feof(ReadFile)){

        if(i32LineIndex == 0) {
            char Data[1024] = {0x0};

            fscanf(ReadFile, "%s", Data);


            i32LineIndex++;

            continue;
        } else if(i32LineIndex != 0) {

            /*
             *  typedef struct {
                    double i32Id;         ///< id
                    double dLatitude;   ///< latitude
                    double dLongtitude; ///< longtitude
                    double i32Track_Id;   ///< track_id;
                    QString StrTime;    ///< time
                }ST_GPS_POINT;
              */
            ST_GPS_POINT stGPSPoint;


            char TempLine[1024] = {0x0};

            fscanf(ReadFile, "%s", TempLine);

            QString TempPrint = QString(TempLine);

            QString StrTempData;

            /**
             * "id","latitude","longitude","track_id","time"
             * 1, -10.9393413858164, -37.0627421097422, 1, "2014-09-13 07:24:32"
             */
            QStringList tempStrList = TempPrint.split(",");
            for(int i32Temp = 0; i32Temp < tempStrList.count(); i32Temp++) {
//                qDebug()<<tempStrList.at(i32Temp);

                if(i32Temp == 0) {
                    stGPSPoint.dId = tempStrList.at(i32Temp).toInt();
                }


                if(i32Temp == 1) {
                    stGPSPoint.dLatitude = tempStrList.at(i32Temp).toDouble();
//                    qDebug()<<QString::number(86) + ": stGPSPoint.dLatitude =  " + QString::number(stGPSPoint.dLatitude);
                }

                if(i32Temp == 2) {
                    stGPSPoint.dLongtitude = tempStrList.at(i32Temp).toDouble();
//                    qDebug()<<QString::number(91) + ": stGPSPoint.dLongtitude =  " + QString::number(stGPSPoint.dLongtitude);
                }

                if(i32Temp == 3) {
                    stGPSPoint.i32Track_Id = tempStrList.at(i32Temp).toInt();
//                    qDebug()<<QString::number(96) + ": stGPSPoint.i32Track_Id =  " + QString::number(stGPSPoint.i32Track_Id);
                }

                if(i32Temp == 4) {
                    stGPSPoint.StrTime = tempStrList.at(i32Temp);
                }

            }

            VecStGPSPoint.append(stGPSPoint);

            QMap<int, QVector<ST_GPS_POINT>>::iterator MapVecGPSPointIter = MapVecGPSPoint.find(stGPSPoint.i32Track_Id);

            if(MapVecGPSPointIter == MapVecGPSPoint.end()) {
//                qDebug()<<"Canot Find it";
                MapVecGPSPoint.insert(stGPSPoint.i32Track_Id, VecStGPSPoint);
                VecStGPSPoint.clear();
            } else {
//                qDebug()<<"Find it ===============  stGPSPoint.i32Track_Id =  " + QString::number(stGPSPoint.i32Track_Id) + " || MapVecGPSPointIter.key = " + QString(MapVecGPSPointIter.key());
                MapVecGPSPoint.erase(MapVecGPSPointIter);
                MapVecGPSPoint.insert(stGPSPoint.i32Track_Id, VecStGPSPoint);


            }

//            vecSTPM.push_back(stPMDataTemp);

        }

#if 1
        if(i32LineIndex > MAXLINE) {
            /**
             * 取测试数据
             **/
            break;
        }
#endif

        i32LineIndex++;

    }
#if 0
    qDebug()<<"i32LineIndex = " + QString::number(i32LineIndex);
#endif
#if 0
    QMap<int, QVector<ST_GPS_POINT>>::iterator MapVecGPSPointIter = MapVecGPSPoint.begin();

    for(MapVecGPSPointIter; MapVecGPSPointIter != MapVecGPSPoint.end(); MapVecGPSPointIter++) {
        qDebug()<<"Key = " + QString::number(MapVecGPSPointIter.key());
        QVector<ST_GPS_POINT> VecstGPSPoint = MapVecGPSPointIter.value();
        for(int i32TempIndex = 0; i32TempIndex < VecstGPSPoint.size(); i32TempIndex++) {
            ST_GPS_POINT stGPSPoint = VecstGPSPoint.at(i32TempIndex);
            qDebug()<<"i32TempIndex = " + QString::number(i32TempIndex) + " || " + QString::number(stGPSPoint.dLatitude) + " , " + QString::number(stGPSPoint.dLongtitude) + " || " + QString::number(stGPSPoint.i32Track_Id);
        }
    }

#endif


    i32LineIndex = 0;

    while(!feof(ReadFile2)){
        if(i32LineIndex == 0) {
            char Data[1024] = {0x0};

            fscanf(ReadFile2, "%s", Data);


            i32LineIndex++;

            continue;
        } else if(i32LineIndex != 0) {

            /**
             * typedef struct {
                    int i32Index;           ///< 序号
                    double dId;            ///< id
                    int i32Id_Android;     ///< id_android
                    double dSpeed;            ///< speed
                    double dTime;            ///< time
                    double dDistance;            ///< distance
                    int i32Rating;             ///< rating
                    int i32Rating_bus;             ///< rating_bus
                    int i32Rating_weather;             ///< rating_weather
                    int dCarORBus;                  /// car or bus
                    QString StrLinha;           /// linha
                }ST_GPS_DATA;
              **/
            ST_GPS_DATA stGPSData;


            char TempLine[1024] = {0x0};

            fscanf(ReadFile2, "%s", TempLine);

            QString TempPrint = QString(TempLine);

            QString StrTempData;

            /**
             * "id","id_android","speed","time","distance","rating","rating_bus","rating_weather","car_or_bus","linha"
             * 1,0,19.2105856218409,0.138048888888889,2.652,3,0,0,1,""
             * 类型：
             */
            QStringList tempStrList = TempPrint.split(",");
            for(int i32Temp = 0; i32Temp < tempStrList.count(); i32Temp++) {
                if(i32Temp == 0) {
                    stGPSData.i32Id = tempStrList.at(i32Temp).toDouble();
                }

                if(i32Temp == 1) {
                    stGPSData.i32Id_Android = tempStrList.at(i32Temp).toInt();
                }

                if(i32Temp == 2) {
                    stGPSData.dSpeed = tempStrList.at(i32Temp).toDouble();
//                    qDebug()<<"line 187 stGPSData.dSpeed = " + QString::number(stGPSData.dSpeed);
                }

                if(i32Temp == 3) {
                    stGPSData.dTime = tempStrList.at(i32Temp).toDouble();
//                    qDebug()<<"line 192 stGPSData.dTime = " + QString::number(stGPSData.dTime);
                }

                if(i32Temp == 4) {
                    stGPSData.dDistance = tempStrList.at(i32Temp).toDouble();
                }

                if(i32Temp == 5) {
                    stGPSData.i32Rating = tempStrList.at(i32Temp).toInt();
                }

                if(i32Temp == 6) {
                    stGPSData.i32Rating_bus = tempStrList.at(i32Temp).toInt();
                }

                if(i32Temp == 7) {
                    stGPSData.i32Rating_weather = tempStrList.at(i32Temp).toInt();
                }

                if(i32Temp == 8) {
                    stGPSData.dCarORBus = tempStrList.at(i32Temp).toDouble();
                }

                if(i32Temp == 9) {
                    stGPSData.StrLinha = tempStrList.at(i32Temp);
                }

//                VecStDevData.append(stGPSData);

            }
            QMap<int, QVector<ST_GPS_POINT>>::iterator MapVecGPSPointIter = MapVecGPSPoint.find(stGPSData.i32Id);

            if(MapVecGPSPointIter == MapVecGPSPoint.end()) {

            } else {
                /**
                 * 找到对应的设备
                 **/
                ST_DEVICE_DATA stDevData;
                stDevData.VecStGPSPoint = MapVecGPSPointIter.value();
                stDevData.stGPSData = stGPSData;
                MapIntDeviceData.insert(stGPSData.i32Id, stDevData);
            }

//            qDebug()<<"Show Other Data";

            i32LineIndex++;
        }
    }



#if 0
    qDebug()<<"Show Result:";
    QMap<int, ST_DEVICE_DATA>::iterator MapIntDeviceDataIter = MapIntDeviceData.begin();
    for(MapIntDeviceDataIter; MapIntDeviceDataIter != MapIntDeviceData.end(); MapIntDeviceDataIter++) {
        qDebug()<<"Key = " + QString::number(MapIntDeviceDataIter.key());
        ST_DEVICE_DATA stDevData = MapIntDeviceDataIter.value();

        ST_GPS_DATA TempGpsData = stDevData.stGPSData;
        qDebug()<<"i32Index = " + QString::number(TempGpsData.i32Index);
        qDebug()<<"i32Id = " + QString::number(TempGpsData.i32Id);
        qDebug()<<"i32Id_Android = " + QString::number(TempGpsData.i32Id_Android);
        qDebug()<<"dSpeed = " + QString::number(TempGpsData.dSpeed);
        qDebug()<<"dTime = " + QString::number(TempGpsData.dTime);
        qDebug()<<"dDistance = " + QString::number(TempGpsData.dDistance);
        qDebug()<<"i32Rating = " + QString::number(TempGpsData.i32Rating);
        qDebug()<<"i32Rating_bus = " + QString::number(TempGpsData.i32Rating_bus);
        qDebug()<<"i32Rating_weather = " + QString::number(TempGpsData.i32Rating_weather);
        qDebug()<<"dCarORBus = " + QString::number(TempGpsData.dCarORBus);
        qDebug()<<"StrLinha = " + TempGpsData.StrLinha;

        QVector<ST_GPS_POINT> VecStGPSPointTemp = stDevData.VecStGPSPoint;
        for(int i32TempIndex = 0; i32TempIndex < VecStGPSPointTemp.size(); i32TempIndex++) {
            ST_GPS_POINT stGPSPoint = VecStGPSPointTemp.at(i32TempIndex);
            qDebug()<<"i32TempIndex = " + QString::number(i32TempIndex) + " || " + QString::number(stGPSPoint.dLatitude) + " , " + QString::number(stGPSPoint.dLongtitude) + " || i32Track_Id = " + QString::number(stGPSPoint.i32Track_Id);

        }
    }



#endif

    qDebug()<<"Read file finish";
    fclose(ReadFile);
    fclose(ReadFile2);


    return EXIT_SUCCESS;
}

/**
 * @brief CprocessData::LoadDataLabels
 * @return
 * 给数据加标签
 */
int CprocessData::LoadDataLabels()
{
    qDebug()<<"WriteFile:";
    FILE *WriteFileIdle;
    FILE *WriteFileIdle2;

    WriteFileIdle = fopen("RBFNN/DataFile.txt", "wb+");
    WriteFileIdle2 = fopen("RBFNN/DataInputNetFile.csv", "wb+");
    if(WriteFileIdle == NULL){
        qDebug()<<"OpenWriteFile ERROR";
        return EXIT_FAILURE;
    }
    if(WriteFileIdle2 == NULL){
        qDebug()<<"OpenWriteFile2 ERROR";
        return EXIT_FAILURE;
    }
    char WriteData[1024] = {0x0};
    char WriteNetInput[1024] = {0x0};

    // 获得当前数据值用于求差，并保存
    int i32Tempi32Id_Android = -1;
    double i32TempdSpeed = -1;
    double i32TempdTime = -1;
    double i32TempdDistance = -1;
    int i32Tempi32Rating = -1;
    int i32Tempi32Rating_bus = -1;
    int i32Tempi32Rating_weather = -1;
    int i32TempdCarORBus = -1;
    double i32TempdLatitude = -1;
    double i32TempdLongtitude = -1;

//    // 计算神经网络输入的差值
//    QVector<int> vecDisi32Id_Android;
//    QVector<double> vecDisdSpeed;
//    QVector<double> vecDisdTime;
//    QVector<double> vecDisdDistance;
//    QVector<int> vecDisi32Rating;
//    QVector<int> vecDisi32Rating_bus;
//    QVector<int> vecDisi32Rating_weather;
//    QVector<int> vecDisdCarORBus;
//    QVector<double> vecDisdLatitude;
//    QVector<double> vecDisdLongtitude;

    //用于记录当前id_android
    int i32Tempid = -999;
    // 记录标志位，用于判断是否需要记录，1表示需要记录；0表示不需要记录；-1用于初始化
    int i32RemSignal = -1;

    // 记录经纬度，一组ID中包括多个经纬度标志位，用于判断是否需要记录，1表示需要记录；0表示不需要记录；-1用于初始化
    int i32LatLongSignal = -1;

    QMap<int, ST_DEVICE_DATA>::iterator MapIntDeviceDataIter = MapIntDeviceData.begin();
    for(MapIntDeviceDataIter; MapIntDeviceDataIter != MapIntDeviceData.end(); MapIntDeviceDataIter++) {
//        qDebug()<<"Key = " + QString::number(MapIntDeviceDataIter.key());

        ST_DEVICE_DATA stDevData = MapIntDeviceDataIter.value();
        ST_GPS_DATA TempGpsData = stDevData.stGPSData;

        if(i32Tempid != TempGpsData.i32Id_Android) {
            int i32Tempid = TempGpsData.i32Id_Android;
            if(i32Tempid == -1) {
                // 第一次用记录
                i32RemSignal = 1;
            }else {
                // 不是第一次不需要记录,需要做差
                i32RemSignal = 0;
            }

        } else {
            // 用于做差值
            i32RemSignal = 0;
        }

        sprintf(WriteData, "%d  %d  %d  %d\n", MapIntDeviceDataIter.key(), 2, TempGpsData.i32Id_Android, 0);
        fprintf(WriteFileIdle, "%s", WriteData);
        memset(WriteData, 0x0, sizeof(char) * 1024);

        sprintf(WriteData, "%d	%d	%lf	%d\n", MapIntDeviceDataIter.key(), 3, TempGpsData.dSpeed, 1);
        fprintf(WriteFileIdle, "%s", WriteData);
        memset(WriteData, 0x0, sizeof(char) * 1024);

        sprintf(WriteData, "%d	%d	%lf	%d\n", MapIntDeviceDataIter.key(), 4, TempGpsData.dTime, 1);
        fprintf(WriteFileIdle, "%s", WriteData);
        memset(WriteData, 0x0, sizeof(char) * 1024);

        sprintf(WriteData, "%d	%d	%lf	%d\n", MapIntDeviceDataIter.key(), 5, TempGpsData.dDistance, 1);
        fprintf(WriteFileIdle, "%s", WriteData);
        memset(WriteData, 0x0, sizeof(char) * 1024);

        sprintf(WriteData, "%d	%d	%d	%d\n", MapIntDeviceDataIter.key(), 6, TempGpsData.i32Rating, 0);
        fprintf(WriteFileIdle, "%s", WriteData);
        memset(WriteData, 0x0, sizeof(char) * 1024);

        sprintf(WriteData, "%d	%d	%d	%d\n", MapIntDeviceDataIter.key(), 7, TempGpsData.i32Rating_bus, 0);
        fprintf(WriteFileIdle, "%s", WriteData);
        memset(WriteData, 0x0, sizeof(char) * 1024);

        sprintf(WriteData, "%d	%d	%d	%d\n", MapIntDeviceDataIter.key(), 8, TempGpsData.i32Rating_weather, 2);
        fprintf(WriteFileIdle, "%s", WriteData);
        memset(WriteData, 0x0, sizeof(char) * 1024);

        sprintf(WriteData, "%d	%d	%d	%d\n", MapIntDeviceDataIter.key(), 9, TempGpsData.dCarORBus, 2);
        fprintf(WriteFileIdle, "%s", WriteData);
        memset(WriteData, 0x0, sizeof(char) * 1024);

        if(i32RemSignal == -1) {
            // 记录第一组数据
            i32Tempi32Id_Android = TempGpsData.i32Id_Android;
            i32TempdSpeed = TempGpsData.dSpeed;
            i32TempdTime = TempGpsData.dTime;
            i32TempdDistance = TempGpsData.dDistance;
            i32Tempi32Rating = TempGpsData.i32Rating;
            i32Tempi32Rating_bus = TempGpsData.i32Rating_bus;
            i32Tempi32Rating_weather = TempGpsData.i32Rating_weather;
            i32TempdCarORBus = TempGpsData.dCarORBus;

            i32RemSignal = 0;
        }else if(i32RemSignal == 0) {
            int Writei32Id_Android = -1;
            double WritedSpeed = -1;
            double WritedTime = -1;
            double WritedDistance = -1;
            int Writei32Rating = -1;
            int Writei32Rating_bus = -1;
            int Writei32Rating_weather = -1;
            int WritedCarORBus = -1;

            Writei32Id_Android = abs(abs(TempGpsData.i32Id_Android) - abs(i32Tempi32Id_Android));
            WritedSpeed = fabs(fabs(TempGpsData.dSpeed) - fabs(i32TempdSpeed));
            WritedTime = fabs(fabs(TempGpsData.dTime) - fabs(i32TempdTime));
            WritedDistance = abs(abs(TempGpsData.dDistance) - abs(i32TempdDistance));
            Writei32Rating = abs(abs(TempGpsData.i32Rating) - abs(i32Tempi32Rating));
            Writei32Rating_bus = abs(abs(TempGpsData.i32Rating_bus) - abs(i32Tempi32Rating_bus));
            Writei32Rating_weather = abs(abs(TempGpsData.i32Rating_weather) - abs(i32Tempi32Rating_weather));
            WritedCarORBus = abs(abs(TempGpsData.dCarORBus) - abs(i32TempdCarORBus));

            sprintf(WriteNetInput, "%d %d %d %d\n", MapIntDeviceDataIter.key(), 2, Writei32Id_Android, 0);
//            fwrite(WriteNetInput, strlen(WriteNetInput), 1, WriteFileIdle2);
            fprintf(WriteFileIdle2, "%s", WriteNetInput);
            memset(WriteNetInput, 0x0, sizeof(char) * 1024);

            sprintf(WriteNetInput, "%d %d %lf %d\n", MapIntDeviceDataIter.key(), 3, WritedSpeed, 1);
//            fwrite(WriteNetInput, strlen(WriteNetInput), 1, WriteFileIdle2);
            fprintf(WriteFileIdle2, "%s", WriteNetInput);
            memset(WriteNetInput, 0x0, sizeof(char) * 1024);

            sprintf(WriteNetInput, "%d %d %lf %d\n", MapIntDeviceDataIter.key(), 4, WritedTime, 1);
//            fwrite(WriteNetInput, strlen(WriteNetInput), 1, WriteFileIdle2);
            fprintf(WriteFileIdle2, "%s", WriteNetInput);
            memset(WriteNetInput, 0x0, sizeof(char) * 1024);

            sprintf(WriteNetInput, "%d %d %lf %d\n", MapIntDeviceDataIter.key(), 5, WritedDistance, 1);
//            fwrite(WriteNetInput, strlen(WriteNetInput), 1, WriteFileIdle2);
            fprintf(WriteFileIdle2, "%s", WriteNetInput);
            memset(WriteNetInput, 0x0, sizeof(char) * 1024);

            sprintf(WriteNetInput, "%d %d %d %d\n", MapIntDeviceDataIter.key(), 6, Writei32Rating, 0);
//            fwrite(WriteNetInput, strlen(WriteNetInput), 1, WriteFileIdle2);
            fprintf(WriteFileIdle2, "%s", WriteNetInput);
            memset(WriteNetInput, 0x0, sizeof(char) * 1024);

            sprintf(WriteNetInput, "%d %d %d %d\n", MapIntDeviceDataIter.key(), 7, Writei32Rating_bus, 0);
//            fwrite(WriteNetInput, strlen(WriteNetInput), 1, WriteFileIdle2);
            fprintf(WriteFileIdle2, "%s", WriteNetInput);
            memset(WriteNetInput, 0x0, sizeof(char) * 1024);

            sprintf(WriteNetInput, "%d %d %d %d\n", MapIntDeviceDataIter.key(), 8, Writei32Rating_weather, 2);
//            fwrite(WriteNetInput, strlen(WriteNetInput), 1, WriteFileIdle2);
            fprintf(WriteFileIdle2, "%s", WriteNetInput);
            memset(WriteNetInput, 0x0, sizeof(char) * 1024);

            sprintf(WriteNetInput, "%d %d %d %d\n", MapIntDeviceDataIter.key(), 9, WritedCarORBus, 2);
//            fwrite(WriteNetInput, strlen(WriteNetInput), 1, WriteFileIdle2);
            fprintf(WriteFileIdle2, "%s", WriteNetInput);
            memset(WriteNetInput, 0x0, sizeof(char) * 1024);

            i32Tempi32Id_Android = TempGpsData.i32Id_Android;
            i32TempdSpeed = TempGpsData.dSpeed;
            i32TempdTime = TempGpsData.dTime;
            i32TempdDistance = TempGpsData.dDistance;
            i32Tempi32Rating = TempGpsData.i32Rating;
            i32Tempi32Rating_bus = TempGpsData.i32Rating_bus;
            i32Tempi32Rating_weather = TempGpsData.i32Rating_weather;
            i32TempdCarORBus = TempGpsData.dCarORBus;

        }

        char WriteLatLong[1024] = {0x0};
        QVector<ST_GPS_POINT> VecStGPSPointTemp = stDevData.VecStGPSPoint;
        for(int i32TempIndex = 0; i32TempIndex < VecStGPSPointTemp.size(); i32TempIndex++) {
            if(i32LatLongSignal == -1) {
                // 第一次用于记录
                i32LatLongSignal = 1;
            }
            ST_GPS_POINT stGPSPoint = VecStGPSPointTemp.at(i32TempIndex);
//            qDebug()<<"i32TempIndex = " + QString::number(i32TempIndex) + " || " + QString::number(stGPSPoint.dLatitude) + " , " + QString::number(stGPSPoint.dLongtitude) + " || i32Track_Id = " + QString::number(stGPSPoint.i32Track_Id);

            sprintf(WriteData, "%d  %d  %lf %d\n", MapIntDeviceDataIter.key(), 10, stGPSPoint.dLatitude, 3);
            fprintf(WriteFileIdle, "%s", WriteData);
            memset(WriteData, 0x0, sizeof(char) * 1024);

            sprintf(WriteData, "%d  %d  %lf %d\n", MapIntDeviceDataIter.key(), 11, stGPSPoint.dLongtitude, 3);
            fprintf(WriteFileIdle, "%s", WriteData);
            memset(WriteData, 0x0, sizeof(char) * 1024);

            if(i32LatLongSignal == 1) {
                //记录数据
                i32TempdLatitude = stGPSPoint.dLatitude;
                i32TempdLongtitude = stGPSPoint.dLongtitude;

                // 置为0用于做差值
                i32LatLongSignal = 0;
            } else if(i32LatLongSignal == 0){
                double WriteLatitude = fabs(fabs(stGPSPoint.dLatitude)-fabs(i32TempdLatitude));
                double WriteLongtitude = fabs(fabs(stGPSPoint.dLongtitude)-fabs(i32TempdLongtitude));

                sprintf(WriteLatLong, "%d %d %lf %d\n", MapIntDeviceDataIter.key(), 10, WriteLatitude, 3);
                fwrite(WriteLatLong, strlen(WriteLatLong), 1, WriteFileIdle2);
//                fprintf(WriteFileIdle2, "%s", WriteNetInput);
                memset(WriteLatLong, 0x0, sizeof(char) * 1024);

                sprintf(WriteLatLong, "%d %d %lf %d\n", MapIntDeviceDataIter.key(), 11, WriteLongtitude, 3);
                fwrite(WriteLatLong, strlen(WriteLatLong), 1, WriteFileIdle2);
//                fprintf(WriteFileIdle2, "%s", WriteNetInput);
                memset(WriteLatLong, 0x0, sizeof(char) * 1024);
            }

        }
        i32LatLongSignal = -1;

    }

    fclose(WriteFileIdle);
    qDebug()<<"Write File Finish";
    qDebug()<<"Write File2 Finish";




}

/**
 * @brief CprocessData::loadTrainingData
 * @return
 * 给训练数据加标签
 */
int CprocessData::loadTrainingData()
{

#if 0
    /// 查错
    int i32TempCount = 0;
    int i32Sum = 0;
#endif

    QMap<int, ST_DEVICE_DATA>::iterator MapIntDeviceDataIter = MapIntDeviceData.begin();
    for(MapIntDeviceDataIter; MapIntDeviceDataIter != MapIntDeviceData.end(); MapIntDeviceDataIter++) {
        /**
         *   id, id_android,       speed,        time, distance, rating, rating_bus, rating_weather, car_or_bus, linha,     latitude,    longitude, track_id,           time
         *    1,          0, 19.21058562, 0.138048889,    2.652,      3,          0,              0,          1,    NA, -10.93934139, -37.06274211,        1, 2014/9/13 7:24
         * Type,          1,           2,           2,        2,      1,          1,              3,          3,      ,            4,            4,
         **/
        ST_DEVICE_DATA stDevDataTemp = MapIntDeviceDataIter.value();
//        training_point[0].push_back(stDevDataTemp.stGPSData.i32Id);
        training_point[0].push_back(stDevDataTemp.stGPSData.i32Id_Android);
//        qDebug()<<"training_point[0] = " + QString::number(stDevDataTemp.stGPSData.i32Id_Android);
//        training_labels.push_back(1);

//        training_point[1].push_back(stDevDataTemp.stGPSData.i32Id);
        training_point[1].push_back(stDevDataTemp.stGPSData.dSpeed);
//        qDebug()<<"training_point[1] = " + QString::number(stDevDataTemp.stGPSData.dSpeed);
//        training_labels.push_back(2);

        training_point[1].push_back(stDevDataTemp.stGPSData.dTime);
//        qDebug()<<"training_point[1] = " + QString::number(stDevDataTemp.stGPSData.dTime);
//        training_labels.push_back(2);

        training_point[1].push_back(stDevDataTemp.stGPSData.dDistance);
//        qDebug()<<"training_point[1] = " + QString::number(stDevDataTemp.stGPSData.dDistance);
//        training_labels.push_back(2);

        training_point[0].push_back(stDevDataTemp.stGPSData.i32Rating);
//        qDebug()<<"training_point[2] = " + QString::number(stDevDataTemp.stGPSData.i32Rating);
//        training_labels.push_back(3);

        training_point[0].push_back(stDevDataTemp.stGPSData.i32Rating_bus);
//        qDebug()<<"training_point[2] = " + QString::number(stDevDataTemp.stGPSData.i32Rating_bus);
//        training_labels.push_back(3);

//        training_point[2].push_back(stDevDataTemp.stGPSData.i32Id);
        training_point[2].push_back(stDevDataTemp.stGPSData.i32Rating_weather);
//        qDebug()<<"training_point[3] = " + QString::number(stDevDataTemp.stGPSData.i32Rating_weather);
//        training_labels.push_back(4);

        training_point[2].push_back(stDevDataTemp.stGPSData.dCarORBus);
//        qDebug()<<"training_point[3] = " + QString::number(stDevDataTemp.stGPSData.dCarORBus);
//        training_labels.push_back(4);

        QVector<ST_GPS_POINT> VecStGPSPointTemp = stDevDataTemp.VecStGPSPoint;

#if 0
        /// 打印
        qDebug()<<"Line355: VecStGpsPointSize = " + QString::number(VecStGPSPointTemp.size());
        i32Sum += VecStGPSPointTemp.size();
#endif
        for(int i32TempIndex1 = 0; i32TempIndex1 < VecStGPSPointTemp.size(); i32TempIndex1++) {
//            training_point[3].push_back(VecStGPSPointTemp.at(i32TempIndex1).i32Track_Id);
            training_point[3].push_back(VecStGPSPointTemp.at(i32TempIndex1).dLatitude);

            training_point[3].push_back(VecStGPSPointTemp.at(i32TempIndex1).dLongtitude);
        }

#if 0
        /// 查错
        i32TempCount++;
#endif

    }
#if 0
    /// 打印
    qDebug()<<"i32Sum = " + QString::number(i32Sum) + " || i32TempCount = " + QString::number(i32TempCount) + "point[3] = " + QString::number(training_point[3].size());
#endif

    for(int i32TempIndex0 = 0; i32TempIndex0 < MAXCLASS; i32TempIndex0++) {
        training_data.push_back(training_point[i32TempIndex0]);
        training_labels.push_back(i32TempIndex0 + 1);
    }


#if 0
    qDebug()<<"SHow the train Data";
    for(int i32TempIndex0 = 0; i32TempIndex0 < 1; i32TempIndex0++) {
        qDebug()<<"i32TempIndex = " + QString::number(i32TempIndex0) + " || size = " + QString::number(training_data.at(i32TempIndex0).size());
        datapoint TempData = training_data.at(i32TempIndex0);
        for(int i32TempIndex1 = 0; i32TempIndex1 < TempData.size(); i32TempIndex1++) {
            qDebug()<<"i32TempIndex1 = " + QString::number(i32TempIndex1) + " || data = " + QString::number(TempData.at(i32TempIndex1));
        }
    }
#endif

}

/**
 * @brief CprocessData::WriteFile
 * @param Train_Test
 * @return
 * 保存测试或者训练数据，1，训练数据；2，测试数据
 */
int CprocessData::WriteFile()
{
    FILE *WriteFileIdle;

    WriteFileIdle = fopen("RBFNN/TrainFile.txt", "wb+");
    for(int i32TempIndex = 0; i32TempIndex < training_data.size(); i32TempIndex++) {
        datapoint TempData = training_data.at(i32TempIndex);
        qDebug()<<"i32TempIndex = " + QString::number(i32TempIndex) + " || " + QString::number(TempData.size());
        for(int i32TempIndex2 = 0; i32TempIndex2 < TempData.size(); i32TempIndex2++) {
//            QString TempWriteData = QString::number(TempData.at(i32TempIndex2)) + " " + QString::number(i32TempIndex);
            char WriteData[1024] = {0x0};
            sprintf(WriteData, "%lf %d\n", TempData.at(i32TempIndex2), i32TempIndex);
//            fwrite(WriteData, sizeof(WriteData), 1, WriteFileIdle);
            fprintf(WriteFileIdle, "%s", WriteData);
        }

    }

    fclose(WriteFileIdle);
    qDebug()<<"Write File Finish";
}



CprocessData::~CprocessData()
{

}
