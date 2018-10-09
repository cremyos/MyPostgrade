#include "cshowdata.h"
#include "ui_cshowdata.h"

CShowData::CShowData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CShowData)
{
    ui->setupUi(this);

    rfd.ReadData();

    imageEnable.load("Pic/Green.png");
    imageDisable.load("Pic/Red.png");

    ShowTheRes(ui->widget);
}

int CShowData::ShowTheRes(QCustomPlot *CustomPlot)
{
    /**
     * @brief plotGradient
     * 配置需要绘制的坐标曲线
     */
    QLinearGradient plotGradient;
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    ui->widget->setBackground(plotGradient);
    //设置坐标颜色/坐标名称颜色
    ui->widget->xAxis->setLabelColor(Qt::white);//文字颜色
    ui->widget->yAxis->setLabelColor(Qt::white);
    ui->widget->xAxis->setTickLabelColor(Qt::white);//坐标轴数字颜色
    ui->widget->yAxis->setTickLabelColor(Qt::white);
    ui->widget->xAxis->setBasePen(QPen(Qt::white, 1));//坐标轴颜色及宽度
    ui->widget->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->widget->xAxis->setTickPen(QPen(Qt::white, 1));//主刻度
    ui->widget->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget->xAxis->setSubTickPen(QPen(Qt::white, 1));//副刻度
    ui->widget->yAxis->setSubTickPen(QPen(Qt::white, 1));

    /**
     * 读取文本中的数据
     */
    QVector<double> CruveLine;
    QVector<double> CruveIndexVec;
    int CruveIndex = 0;
    QMap<int, QVector<ST_CLASS_DATA_SHOWTYPE>>::iterator MapVecSTCDSIter = rfd.MapVecSTCDS.begin();
    for(MapVecSTCDSIter; MapVecSTCDSIter != rfd.MapVecSTCDS.end(); MapVecSTCDSIter++) {
        qDebug()<<"Number = " + QString::number(MapVecSTCDSIter.key());
        ui->label_class->setText(QString::number(MapVecSTCDSIter.key()));
        QVector<ST_CLASS_DATA_SHOWTYPE> VecStCDS = MapVecSTCDSIter.value();
        for(int i32TempIndex = 0; i32TempIndex < VecStCDS.size(); i32TempIndex++) {
            ST_CLASS_DATA_SHOWTYPE stCDS = VecStCDS.at(i32TempIndex);
            switch(stCDS.i32ShowType) {
                /**
                 * 1:LCD数字显示
                 * 2：普通数字显示
                 * 3：使能开关
                 * 4：曲线图
                 **/
                case 0: {
//                    qDebug()<<"case 0: " + QString::number(stCDS.i32ShowType);
//                    qDebug()<<"data: " + QString::number(stCDS.dData);
                    ui->lcdNumber->display(stCDS.dData);
                    break;
                }
                case 1: {
//                    qDebug()<<"case 1: " + QString::number(stCDS.i32ShowType);
                    ui->textBrowser->append(QString::number(stCDS.dData));
                    break;
                }
                case 2: {
//                    qDebug()<<"case 2: " + QString::number(stCDS.i32ShowType);
                    if(stCDS.dData == 1) {
                        /**
                         * 有效
                         **/
                        ui->label_Enable->setPixmap(imageEnable);
                    } else if(stCDS.dData == 0) {
                        /**
                         * 无效
                         **/
                        ui->label_Disable->setPixmap(imageDisable);
                    }
                    break;
                }
                case 3: {
//                    qDebug()<<"case 3: " + QString::number(stCDS.i32ShowType);
                    QString TempShowData = QString::number(stCDS.dData) + "曲线表示";
//                    ui->textBrowser_2->append(TempShowData);
                    /**
                     * 数据
                     **/
                    CruveLine.append(stCDS.dData);
                    CruveIndexVec.append(CruveIndex);
                    CruveIndex++;
                    break;
                }

            }
        }

    }
    //设置属性可缩放，移动等
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                         QCP::iSelectLegend | QCP::iSelectPlottables);
    CustomPlot->addGraph();//添加一条曲线
    CustomPlot->graph(0)->setPen(QPen(Qt::green)); //0是曲线序号，添加的第一条是0，设置曲线颜色
    CustomPlot->graph(0)->setData(CruveIndexVec,CruveLine); //输出各点的图像，x和y都是QVector类
    CustomPlot->xAxis->setLabel("x");//x轴的文字
    CustomPlot->yAxis->setLabel("y");//y轴的文字

    CustomPlot->xAxis->setRange(0,1000);//x轴范围
    CustomPlot->yAxis->setRange(-10.8600,-10.8700);//y轴范围

}

CShowData::~CShowData()
{
    delete ui;
}
