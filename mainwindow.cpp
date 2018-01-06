#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "defines.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // lineEdit_City init.
    m_pCpCityEdit = new QCompleter(QStringList(), this);
    ui->lineEdit_City->setCompleter(m_pCpCityEdit);
    ui->lineEdit_City->setAttribute(Qt::WA_InputMethodEnabled,true);
    ui->lineEdit_City->installEventFilter(this);

    // lineEdit_Area init.
    m_pCpAreaEdit = new QCompleter(QStringList(), this);
    ui->lineEdit_Area->setCompleter(m_pCpAreaEdit);
    ui->lineEdit_Area->setAttribute(Qt::WA_InputMethodEnabled,true);
    ui->lineEdit_Area->installEventFilter(this);

    // home phone
    m_homePhoneValid = new QRegExpValidator(QRegExp("[0][0-9]{8,9}"), this);

    //cellphone
    m_cellPhoneValid = new QRegExpValidator(QRegExp("[0][9][0-9]{8,8}"), this);

    // EMAIL
    m_mailList << "gmail.com" << "hotmail.com" << "yahoo.com.tw" << "msn.com" << "msa.hinet.net";
    m_pCpEmail = new QCompleter(QStringList(), this);
    m_pCpEmail->setCompletionMode(QCompleter::InlineCompletion);
    ui->lineEdit_Email->setCompleter(m_pCpEmail);
    m_mailValid = new QRegExpValidator(QRegExp("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}\\b"), this);

    // PI
    m_pi = new QProgressIndicator(this);
    ui->horizontalLayout_2->addWidget(m_pi);

    // CONTACT
    ui->radioButton->installEventFilter(this);
    ui->radioButton_2->installEventFilter(this);

    loadCityAndArea();

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionReadMe, SIGNAL(triggered()), this, SLOT(readMe()));

    m_nSubmit = 0;
    setLabelNumText(m_nSubmit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAreaListFromCityIdx(int cityIdx)
{
    ui->listWidget_Area->clear();
    ui->listWidget_Area->addItems(m_areaStr[cityIdx].toList());

    QStringListModel *model = (QStringListModel*)(m_pCpAreaEdit->model());
    model->setStringList(m_areaStr[cityIdx].toList());
}

void MainWindow::loadCityAndArea()
{
    m_cityStr << QStringLiteral("基隆市")<< QStringLiteral("台北市")<< QStringLiteral("新北市")<< QStringLiteral("桃園市")
              << QStringLiteral("新竹市")<< QStringLiteral("新竹縣")<< QStringLiteral("苗栗縣")<< QStringLiteral("台中市")
              << QStringLiteral("彰化縣")<< QStringLiteral("南投縣")<< QStringLiteral("雲林縣")<< QStringLiteral("嘉義市")
              << QStringLiteral("嘉義縣")<< QStringLiteral("台南市")<< QStringLiteral("高雄市")<< QStringLiteral("屏東縣")
              << QStringLiteral("台東縣")<< QStringLiteral("花蓮縣")<< QStringLiteral("宜蘭縣")<< QStringLiteral("澎湖縣")
              << QStringLiteral("金門縣")<< QStringLiteral("連江縣");
    ui->listWidget_City->addItems(m_cityStr.toList());

    QStringListModel *model = (QStringListModel*)(m_pCpCityEdit->model());
    model->setStringList(m_cityStr.toList());

    QVector<QString> areas;

    areas.clear();
    areas << QStringLiteral("中正區") << QStringLiteral("七堵區") << QStringLiteral("暖暖區") << QStringLiteral("仁愛區") << QStringLiteral("中山區") << QStringLiteral("安樂區") << QStringLiteral("信義區");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("松山區") << QStringLiteral("信義區") << QStringLiteral("大安區") << QStringLiteral("中山區") << QStringLiteral("中正區") << QStringLiteral("大同區") << QStringLiteral("萬華區") << QStringLiteral("文山區") << QStringLiteral("南港區") << QStringLiteral("內湖區") << QStringLiteral("士林區") << QStringLiteral("北投區");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("板橋區") << QStringLiteral("三重區") << QStringLiteral("中和區") << QStringLiteral("永和區") << QStringLiteral("新莊區") << QStringLiteral("新店區") << QStringLiteral("樹林區") << QStringLiteral("鶯歌區") << QStringLiteral("三峽區") << QStringLiteral("淡水區") << QStringLiteral("汐止區") << QStringLiteral("瑞芳區") << QStringLiteral("土城區") << QStringLiteral("蘆洲區") << QStringLiteral("五股區") << QStringLiteral("泰山區") << QStringLiteral("林口區") << QStringLiteral("深坑區") << QStringLiteral("石碇區") << QStringLiteral("坪林區") << QStringLiteral("三芝區") << QStringLiteral("石門區") << QStringLiteral("八里區") << QStringLiteral("平溪區") << QStringLiteral("雙溪區") << QStringLiteral("貢寮區") << QStringLiteral("金山區") << QStringLiteral("萬里區") << QStringLiteral("烏來區");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("桃園區") << QStringLiteral("中壢區") << QStringLiteral("大溪區") << QStringLiteral("楊梅區") << QStringLiteral("蘆竹區") << QStringLiteral("大園區") << QStringLiteral("龜山區") << QStringLiteral("八德區") << QStringLiteral("龍潭區") << QStringLiteral("平鎮區") << QStringLiteral("新屋區") << QStringLiteral("觀音區") << QStringLiteral("復興區");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("東區") << QStringLiteral("北區") << QStringLiteral("香山區");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("竹北市") << QStringLiteral("竹東鎮") << QStringLiteral("新埔鎮") << QStringLiteral("關西鎮") << QStringLiteral("湖口鄉") << QStringLiteral("新豐鄉") << QStringLiteral("芎林鄉") << QStringLiteral("橫山鄉") << QStringLiteral("北埔鄉") << QStringLiteral("寶山鄉") << QStringLiteral("峨眉鄉") << QStringLiteral("尖石鄉") << QStringLiteral("五峰鄉");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("苗栗市") << QStringLiteral("苑裡鎮") << QStringLiteral("通霄鎮") << QStringLiteral("竹南鎮") << QStringLiteral("頭份鎮") << QStringLiteral("後龍鎮") << QStringLiteral("卓蘭鎮") << QStringLiteral("大湖鄉") << QStringLiteral("公館鄉") << QStringLiteral("銅鑼鄉") << QStringLiteral("南庄鄉") << QStringLiteral("頭屋鄉") << QStringLiteral("三義鄉") << QStringLiteral("西湖鄉") << QStringLiteral("造橋鄉") << QStringLiteral("三灣鄉") << QStringLiteral("獅潭鄉") << QStringLiteral("泰安鄉");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("中區") << QStringLiteral("東區") << QStringLiteral("南區") << QStringLiteral("西區") << QStringLiteral("北區") << QStringLiteral("西屯區") << QStringLiteral("南屯區") << QStringLiteral("北屯區") << QStringLiteral("豐原區") << QStringLiteral("東勢區") << QStringLiteral("大甲區") << QStringLiteral("清水區") << QStringLiteral("沙鹿區") << QStringLiteral("梧棲區") << QStringLiteral("后里區") << QStringLiteral("神岡區") << QStringLiteral("潭子區") << QStringLiteral("大雅區") << QStringLiteral("新社區") << QStringLiteral("石岡區") << QStringLiteral("外埔區") << QStringLiteral("大安區") << QStringLiteral("烏日區") << QStringLiteral("大肚區") << QStringLiteral("龍井區") << QStringLiteral("霧峰區") << QStringLiteral("太平區") << QStringLiteral("大里區") << QStringLiteral("和平區");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("彰化市") << QStringLiteral("鹿港鎮") << QStringLiteral("和美鎮") << QStringLiteral("線西鄉") << QStringLiteral("伸港鄉") << QStringLiteral("福興鄉") << QStringLiteral("秀水鄉") << QStringLiteral("花壇鄉") << QStringLiteral("芬園鄉") << QStringLiteral("員林鎮") << QStringLiteral("溪湖鎮") << QStringLiteral("田中鎮") << QStringLiteral("大村鄉") << QStringLiteral("埔鹽鄉") << QStringLiteral("埔心鄉") << QStringLiteral("永靖鄉") << QStringLiteral("社頭鄉") << QStringLiteral("二水鄉") << QStringLiteral("北斗鎮") << QStringLiteral("二林鎮") << QStringLiteral("田尾鄉") << QStringLiteral("埤頭鄉") << QStringLiteral("芳苑鄉") << QStringLiteral("大城鄉") << QStringLiteral("竹塘鄉") << QStringLiteral("溪州鄉");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("南投市") << QStringLiteral("埔里鎮") << QStringLiteral("草屯鎮") << QStringLiteral("竹山鎮") << QStringLiteral("集集鎮") << QStringLiteral("名間鄉") << QStringLiteral("鹿谷鄉") << QStringLiteral("中寮鄉") << QStringLiteral("魚池鄉") << QStringLiteral("國姓鄉") << QStringLiteral("水里鄉") << QStringLiteral("信義鄉") << QStringLiteral("仁愛鄉");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("斗六市") << QStringLiteral("斗南鎮") << QStringLiteral("虎尾鎮") << QStringLiteral("西螺鎮") << QStringLiteral("土庫鎮") << QStringLiteral("北港鎮") << QStringLiteral("古坑鄉") << QStringLiteral("大埤鄉") << QStringLiteral("莿桐鄉") << QStringLiteral("林內鄉") << QStringLiteral("二崙鄉") << QStringLiteral("崙背鄉") << QStringLiteral("麥寮鄉") << QStringLiteral("東勢鄉") << QStringLiteral("褒忠鄉") << QStringLiteral("台西鄉") << QStringLiteral("元長鄉") << QStringLiteral("四湖鄉") << QStringLiteral("口湖鄉") << QStringLiteral("水林鄉");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("東區") << QStringLiteral("西區");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("太保市") << QStringLiteral("朴子市") << QStringLiteral("布袋鎮") << QStringLiteral("大林鎮") << QStringLiteral("民雄鄉") << QStringLiteral("溪口鄉") << QStringLiteral("新港鄉") << QStringLiteral("六腳鄉") << QStringLiteral("東石鄉") << QStringLiteral("義竹鄉") << QStringLiteral("鹿草鄉") << QStringLiteral("水上鄉") << QStringLiteral("中埔鄉") << QStringLiteral("竹崎鄉") << QStringLiteral("梅山鄉") << QStringLiteral("番路鄉") << QStringLiteral("大埔鄉") << QStringLiteral("阿里山鄉");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("東區") << QStringLiteral("南區") << QStringLiteral("北區") << QStringLiteral("安南區") << QStringLiteral("安平區") << QStringLiteral("中西區") << QStringLiteral("永康區") << QStringLiteral("仁德區") << QStringLiteral("歸仁區") << QStringLiteral("新營區") << QStringLiteral("鹽水區") << QStringLiteral("白河區") << QStringLiteral("柳營區") << QStringLiteral("後壁區") << QStringLiteral("東山區") << QStringLiteral("麻豆區") << QStringLiteral("下營區") << QStringLiteral("六甲區") << QStringLiteral("官田區") << QStringLiteral("大內區") << QStringLiteral("佳里區") << QStringLiteral("學甲區") << QStringLiteral("西港區") << QStringLiteral("七股區") << QStringLiteral("將軍區") << QStringLiteral("北門區") << QStringLiteral("新化區") << QStringLiteral("善化區") << QStringLiteral("新市區") << QStringLiteral("安定區") << QStringLiteral("山上區") << QStringLiteral("玉井區") << QStringLiteral("楠西區") << QStringLiteral("南化區") << QStringLiteral("左鎮區") << QStringLiteral("關廟區") << QStringLiteral("龍崎區");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("鹽埕區") << QStringLiteral("鼓山區") << QStringLiteral("左營區") << QStringLiteral("楠梓區") << QStringLiteral("三民區") << QStringLiteral("新興區") << QStringLiteral("前金區") << QStringLiteral("苓雅區") << QStringLiteral("前鎮區") << QStringLiteral("旗津區") << QStringLiteral("小港區") << QStringLiteral("鳳山區") << QStringLiteral("林園區") << QStringLiteral("大寮區") << QStringLiteral("大樹區") << QStringLiteral("大社區") << QStringLiteral("仁武區") << QStringLiteral("鳥松區") << QStringLiteral("岡山區") << QStringLiteral("橋頭區") << QStringLiteral("燕巢區") << QStringLiteral("田寮區") << QStringLiteral("阿蓮區") << QStringLiteral("路竹區") << QStringLiteral("湖內區") << QStringLiteral("茄萣區") << QStringLiteral("永安區") << QStringLiteral("彌陀區") << QStringLiteral("梓官區") << QStringLiteral("旗山區") << QStringLiteral("美濃區") << QStringLiteral("六龜區") << QStringLiteral("甲仙區") << QStringLiteral("杉林區") << QStringLiteral("內門區") << QStringLiteral("茂林區") << QStringLiteral("桃源區") << QStringLiteral("那瑪夏區");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("屏東市") << QStringLiteral("潮州鎮") << QStringLiteral("東港鎮") << QStringLiteral("恆春鎮") << QStringLiteral("萬丹鄉") << QStringLiteral("長治鄉") << QStringLiteral("麟洛鄉") << QStringLiteral("九如鄉") << QStringLiteral("里港鄉") << QStringLiteral("鹽埔鄉") << QStringLiteral("高樹鄉") << QStringLiteral("萬巒鄉") << QStringLiteral("內埔鄉") << QStringLiteral("竹田鄉") << QStringLiteral("新埤鄉") << QStringLiteral("枋寮鄉") << QStringLiteral("新園鄉") << QStringLiteral("崁頂鄉") << QStringLiteral("林邊鄉") << QStringLiteral("南州鄉") << QStringLiteral("佳冬鄉") << QStringLiteral("琉球鄉") << QStringLiteral("車城鄉") << QStringLiteral("滿州鄉") << QStringLiteral("枋山鄉") << QStringLiteral("三地門鄉") << QStringLiteral("霧台鄉") << QStringLiteral("瑪家鄉") << QStringLiteral("泰武鄉") << QStringLiteral("來義鄉") << QStringLiteral("春日鄉") << QStringLiteral("獅子鄉") << QStringLiteral("牡丹鄉");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("台東市") << QStringLiteral("成功鎮") << QStringLiteral("關山鎮") << QStringLiteral("卑南鄉") << QStringLiteral("鹿野鄉") << QStringLiteral("池上鄉") << QStringLiteral("東河鄉") << QStringLiteral("長濱鄉") << QStringLiteral("太麻里鄉") << QStringLiteral("大武鄉") << QStringLiteral("綠島鄉") << QStringLiteral("海端鄉") << QStringLiteral("延平鄉") << QStringLiteral("金峰鄉") << QStringLiteral("達仁鄉") << QStringLiteral("蘭嶼鄉");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("花蓮市") << QStringLiteral("鳳林鎮") << QStringLiteral("玉里鎮") << QStringLiteral("新城鄉") << QStringLiteral("吉安鄉") << QStringLiteral("壽豐鄉") << QStringLiteral("光復鄉") << QStringLiteral("豐濱鄉") << QStringLiteral("瑞穗鄉") << QStringLiteral("富里鄉") << QStringLiteral("秀林鄉") << QStringLiteral("萬榮鄉") << QStringLiteral("卓溪鄉");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("宜蘭市") << QStringLiteral("羅東鎮") << QStringLiteral("蘇澳鎮") << QStringLiteral("頭城鎮") << QStringLiteral("礁溪鄉") << QStringLiteral("壯圍鄉") << QStringLiteral("員山鄉") << QStringLiteral("冬山鄉") << QStringLiteral("五結鄉") << QStringLiteral("三星鄉") << QStringLiteral("大同鄉") << QStringLiteral("南澳鄉");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("馬公市") << QStringLiteral("湖西鄉") << QStringLiteral("白沙鄉") << QStringLiteral("西嶼鄉") << QStringLiteral("望安鄉") << QStringLiteral("七美鄉");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("金城鎮") << QStringLiteral("金沙鎮") << QStringLiteral("金湖鎮") << QStringLiteral("金寧鄉") << QStringLiteral("烈嶼鄉") << QStringLiteral("烏坵鄉");
    m_areaStr.append(areas);

    areas.clear();
    areas << QStringLiteral("南竿鄉") << QStringLiteral("北竿鄉") << QStringLiteral("莒光鄉") << QStringLiteral("東引鄉");
    m_areaStr.append(areas);
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if(object == ui->lineEdit_City)
    {
        if(event->type() == QEvent::InputMethod)
        {
            QInputMethodEvent* iEvent = dynamic_cast<QInputMethodEvent*> (event);
            QString s = iEvent->preeditString();
            QString c = iEvent->commitString();
            if(!s.isEmpty())
            {
                ui->lineEdit_City->completer()->setCompletionMode(QCompleter::PopupCompletion);
                ui->lineEdit_City->completer()->setCompletionPrefix(ui->lineEdit_City->text() + s);
                ui->lineEdit_City->completer()->complete();
            }
        }
        return false;
    }
    else if(object == ui->lineEdit_Area)
    {
        if(event->type() == QEvent::InputMethod)
        {
            QInputMethodEvent* iEvent = dynamic_cast<QInputMethodEvent*> (event);
            QString s = iEvent->preeditString();
            if(!s.isEmpty())
            {
                ui->lineEdit_Area->completer()->setCompletionPrefix(ui->lineEdit_Area->text() + s);
                ui->lineEdit_Area->completer()->complete();
            }
        }
        return false;
    }
    else if(object == ui->radioButton)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent* iEvent = dynamic_cast<QKeyEvent*> (event);
            if(iEvent->key() == Qt::Key_Enter || iEvent->key() == Qt::Key_Return)
            {
                QKeyEvent event(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
                QApplication::sendEvent(this, &event);

                return false;
            }
        }

    }
    else if(object == ui->radioButton_2)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent* iEvent = dynamic_cast<QKeyEvent*> (event);
            if(iEvent->key() == Qt::Key_Enter || iEvent->key() == Qt::Key_Return )
            {
                //ui->lineEdit_AddressOther->setFocus();
                QKeyEvent event(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
                QApplication::sendEvent(this, &event);
            }


        }
        return false;
    }

    return QMainWindow::eventFilter(object, event);
}

void MainWindow::on_listWidget_City_itemClicked()
{
    if(ui->listWidget_City->currentRow() >= 0)
    {
        ui->lineEdit_City->setText(ui->listWidget_City->currentItem()->text());
        ui->lineEdit_Area->setFocus();
    }
}

void MainWindow::on_listWidget_Area_itemClicked()
{
    if(ui->listWidget_Area->currentRow() >= 0)
    {
        ui->lineEdit_Area->setText(ui->listWidget_Area->currentItem()->text());
       // ui->lineEdit_VG->setFocus();
        ui->lineEdit_Name->setFocus();
    }
}

void MainWindow::on_lineEdit_City_textChanged(const QString &)
{
    QList<QListWidgetItem *> item = ui->listWidget_City->findItems(ui->lineEdit_City->text(), Qt::MatchExactly);

    ui->lineEdit_Area->clear();
    if(item.size())
    {
        ui->listWidget_City->setCurrentItem(item.at(0));
        int curr_row = ui->listWidget_City->row(item.at(0));
        setAreaListFromCityIdx(curr_row);
    }
    else
    {
        QListWidgetItem * item = ui->listWidget_City->currentItem();
        if(item)
            item->setSelected(false);
        ui->listWidget_Area->clear();
    }
}

void MainWindow::on_lineEdit_Area_textChanged(const QString &)
{
    QList<QListWidgetItem *> item = ui->listWidget_Area->findItems(ui->lineEdit_Area->text(), Qt::MatchExactly);
    if(item.size())
    {
        ui->listWidget_Area->setCurrentItem(item.at(0));
    }
    else
    {
        QListWidgetItem * item = ui->listWidget_Area->currentItem();
        if(item)
            item->setSelected(false);
    }
}

void MainWindow::on_lineEdit_CellPhone_textChanged(const QString &text)
{
    if(text.isEmpty())
    {
        ui->lineEdit_CellPhone->setValidator(NULL);
        ui->lineEdit_CellPhone->setStyleSheet("");
    }
    else
    {
        if(!ui->lineEdit_CellPhone->validator())
            ui->lineEdit_CellPhone->setValidator(m_cellPhoneValid);
        if(!ui->lineEdit_CellPhone->hasAcceptableInput())
            ui->lineEdit_CellPhone->setStyleSheet("border: 2px solid red");
        else
            ui->lineEdit_CellPhone->setStyleSheet("");
    }
}

void MainWindow::on_lineEdit_HomePhone_textChanged(const QString &text)
{
    if(text.isEmpty())
    {
        ui->lineEdit_HomePhone->setValidator(NULL);
        ui->lineEdit_HomePhone->setStyleSheet("");
    }
    else
    {
        if(!ui->lineEdit_HomePhone->validator())
            ui->lineEdit_HomePhone->setValidator(m_homePhoneValid);
        if(!ui->lineEdit_HomePhone->hasAcceptableInput())
            ui->lineEdit_HomePhone->setStyleSheet("border: 2px solid red");
        else
            ui->lineEdit_HomePhone->setStyleSheet("");
    }
}

void MainWindow::on_lineEdit_Email_textChanged(const QString &text)
{
    // Email autocomplete
    // eg. raymond770710@ -> raymond770710@gmail.com
    //                       raymond770710@hotmail.com
    //                       raymond770710@msn.com
    
    QStringListModel* model = (QStringListModel*)m_pCpEmail->model();
    if(text.endsWith(QChar('@')))
    {
        QStringList qsl;
        for (int i = 0; i < m_mailList.count(); i++)
            qsl << (text + m_mailList.at(i));
        m->setStringList(qsl);
    }

    if(text.isEmpty())
    {
        model->setStringList(QStringList());
        ui->lineEdit_Email->setValidator(NULL);
        ui->lineEdit_Email->setStyleSheet("");
    }
    else
    {
        if(!ui->lineEdit_Email->validator())
            ui->lineEdit_Email->setValidator(m_mailValid);
        if(!ui->lineEdit_Email->hasAcceptableInput())
            ui->lineEdit_Email->setStyleSheet("border: 2px solid red");
        else
            ui->lineEdit_Email->setStyleSheet("");
    }
}

void MainWindow::on_lineEdit_City_returnPressed()
{
    if(ui->lineEdit_City->text().isEmpty())
        return;

    QList<QListWidgetItem *> item = ui->listWidget_City->findItems(ui->lineEdit_City->text(), Qt::MatchExactly);

    // If only 1 comletion was matched, set text as currect completion one.
    // eg. 臺北 -> (return pressed) -> 臺北市
    //     彰   -> (return pressed) -> 彰化市
    if(m_pCpCityEdit->completionCount() == 1 && ui->lineEdit_City->text() != m_pCpCityEdit->currentCompletion() )
        ui->lineEdit_City->setText(m_pCpCityEdit->currentCompletion());
    else if(item.size() == 0)
        m_pCpCityEdit->complete();

    item = ui->listWidget_City->findItems(ui->lineEdit_City->text(), Qt::MatchExactly);
    if(item.size()) {
        ui->lineEdit_Area->setFocus();
        ui->lineEdit_Area->selectAll();
    }
}


void MainWindow::on_lineEdit_Area_returnPressed()
{
    if(ui->lineEdit_Area->text().isEmpty())
        return;

    QList<QListWidgetItem *> item = ui->listWidget_Area->findItems(ui->lineEdit_Area->text(), Qt::MatchExactly);
    
    // If only 1 comletion was matched, set text as currect completion one.
    // eg. 士 -> (return pressed) -> 士林區
    if(m_pCpAreaEdit->completionCount() == 1 && ui->lineEdit_Area->text() != m_pCpAreaEdit->currentCompletion()  )
        ui->lineEdit_Area->setText(m_pCpAreaEdit->currentCompletion());
    else if(item.size() == 0)
        m_pCpAreaEdit->complete();

    item = ui->listWidget_Area->findItems(ui->lineEdit_Area->text(), Qt::MatchExactly);
    if(item.size()) {
        ui->lineEdit_Name->setFocus();
    }
}

void MainWindow::on_lineEdit_Name_returnPressed()
{
    if(ui->lineEdit_Name->text().isEmpty())
        return;
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
    ui->radioButton->setFocus();
}

void MainWindow::on_lineEdit_CellPhone_returnPressed()
{
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
}

void MainWindow::on_lineEdit_HomePhone_returnPressed()
{
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
}

void MainWindow::on_lineEdit_Email_returnPressed()
{
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
}

void MainWindow::on_pushButton_Submit_clicked()
{

    ui->actionSubmit->setEnabled(false);
    ui->pushButton_Submit->setEnabled(false);

    bool checked = true;
    QString msg;
    if(ui->lineEdit_City->text().isEmpty()) {
        checked = false;
        msg += QStringLiteral("縣(市)\n");
        ui->lineEdit_City->setFocus();
        goto Flag_Check;
    }

    if(ui->lineEdit_Area->text().isEmpty()) {
        checked = false;
        msg += QStringLiteral("鄉(鎮市區)\n");
        ui->lineEdit_Area->setFocus();
        goto Flag_Check;
    }

    if(ui->lineEdit_Name->text().isEmpty()) {
            checked = false;
            msg += QStringLiteral("提案人\n");
            ui->lineEdit_Name->setFocus();
            goto Flag_Check;
        }

    if(!ui->lineEdit_CellPhone->hasAcceptableInput()) {
            checked = false;
            msg += QStringLiteral("手機格式\n");
            ui->lineEdit_CellPhone->setFocus();
            goto Flag_Check;
        }

    if(!ui->lineEdit_HomePhone->hasAcceptableInput()) {
            checked = false;
            msg += QStringLiteral("市話格式\n");
            ui->lineEdit_HomePhone->setFocus();
            goto Flag_Check;
        }

    if(!ui->lineEdit_Email->hasAcceptableInput()) {
            checked = false;
            msg += QStringLiteral("EMail格式\n");
            ui->lineEdit_Email->setFocus();
            goto Flag_Check;
        }

    if(ui->radioButton->isChecked()) {
        if(ui->lineEdit_CellPhone->text().isEmpty() && ui->lineEdit_HomePhone->text().isEmpty()
                && ui->lineEdit_Email->text().isEmpty()) {
            checked = false;
            msg += QStringLiteral("聯絡方式不能為空\n");
            ui->lineEdit_CellPhone->setFocus();
            goto Flag_Check;
        }
    }
Flag_Check:
    if(!checked) {
            QMessageBox::information(this, QStringLiteral("唉呀！卡彈了 :("),
                                     QStringLiteral("請重新裝填彈藥:\t\t\n%1")
                                     .arg(msg));
            ui->actionSubmit->setEnabled(true);
            ui->pushButton_Submit->setEnabled(true);
            return;
    }


    QUrlQuery urlquery;
    urlquery.addQueryItem(FIELD_NAME, ui->lineEdit_Name->text());
    urlquery.addQueryItem(FIELD_CITY, ui->lineEdit_City->text());
    urlquery.addQueryItem(FIELD_AREA, ui->lineEdit_Area->text());
    if(ui->radioButton->isChecked())
        urlquery.addQueryItem(FIELD_CONTACT_CHK, ui->radioButton->text());
    else
        urlquery.addQueryItem(FIELD_CONTACT_CHK, ui->radioButton_2->text());

    urlquery.addQueryItem(FIELD_HOMEPHONE, ui->lineEdit_HomePhone->text());
    urlquery.addQueryItem(FIELD_CELLPHONE, ui->lineEdit_CellPhone->text());
    urlquery.addQueryItem(FIELD_EMAIL, ui->lineEdit_Email->text());
    urlquery.addQueryItem(FIELD_OTHER_PS, ui->lineEdit_PS->text());
    urlquery.addQueryItem(FIELD_PAGE_HISTORY, "0");

    log_str.clear();

    m_url.setUrl(REQUESET_URL);
    QNetworkRequest request(m_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("User-Agent", "Mozilla Firefox");

    m_pi->startAnimation();
    m_reply = m_qnam.post(request, urlquery.toString(QUrl::FullyEncoded).toUtf8());

    connect(m_reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
    connect(m_reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));

}

void MainWindow::on_pushButton_Reset_clicked()
{
    if(m_nSubmit < MAX_NUM_PER_ROUND) {
        QString title = QStringLiteral("新的一輪");
        QString text = QStringLiteral("本輪擊發次數未滿 50 次。");
        QMessageBox msgBox(QMessageBox::Question, title, text, QMessageBox::Yes | QMessageBox::No, this);
        //msgBox.setText("The document has been modified.");
        msgBox.setInformativeText(QStringLiteral("您想要開始新的一輪嗎？"));
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Yes:
              // Save was clicked
              break;
          case QMessageBox::No:
            return;
            break;
          default:
              // should never be reached
              break;
        }
    }

    ui->lineEdit_City->clear();
    ui->lineEdit_Area->clear();
    ui->lineEdit_Name->clear();
    ui->lineEdit_CellPhone->clear();
    ui->lineEdit_HomePhone->clear();
    ui->lineEdit_Email->clear();
    ui->radioButton->setChecked(true);
    ui->lineEdit_PS->clear();
    emit ui->radioButton->toggle();

    m_nSubmit = 0;
    setLabelNumText(m_nSubmit);
    ui->pushButton_Submit->setEnabled(true);

    ui->lineEdit_City->setFocus();
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    ui->lineEdit_CellPhone->setEnabled(checked);
    ui->lineEdit_CellPhone->clear();
    ui->lineEdit_HomePhone->setEnabled(checked);
    ui->lineEdit_HomePhone->clear();
    ui->lineEdit_Email->setEnabled(checked);
    ui->lineEdit_Email->clear();

    QKeyEvent event(QEvent::KeyPress, Qt::Key_Tab, Qt::NoModifier);
    QApplication::sendEvent(this, &event);
//    if(checked)
//        ui->lineEdit_CellPhone->setFocus();
}

void MainWindow::httpFinished()
{
    ui->actionSubmit->setEnabled(true);
    ui->pushButton_Submit->setEnabled(true);


    bool post_checked = (log_str.indexOf(QStringLiteral("感謝您！")) >= 0) || (log_str.indexOf(QStringLiteral("我們已經收到您回覆的表單。"))>=0);
    m_pi->stopAnimation();
    if (m_reply->error())
    {
        QString  msg= QStringLiteral("送出失敗:( : %1.").arg(m_reply->errorString());
        QMessageBox::information(this, tr("HTTP"), msg);
        //logFile.write((msg + QTime::currentTime().toString()).toUtf8());
        ui->actionSubmit->setEnabled(true);
        ui->pushButton_Submit->setEnabled(true);

    }
    else if(!post_checked)
    {
        QString  msg= QStringLiteral("送出失敗:( : 資料有誤");
        QMessageBox::information(this, tr("HTTP"), msg);
        ui->actionSubmit->setEnabled(true);
        ui->pushButton_Submit->setEnabled(true);
    }
    else
    {
        m_nSubmit++;
        setLabelNumText(m_nSubmit);
        QMessageBox::information(this, QStringLiteral("送出成功 :)"),
                                 QStringLiteral("感謝您 :) 島國又前進了一步"));
        clearAllExceptCityArea();
        if(m_nSubmit >= MAX_NUM_PER_ROUND)
            ui->pushButton_Submit->setEnabled(false);
    }
    m_reply->deleteLater();
    m_reply = 0;

    //logFile.flush();
    //logFile.close();
}

void MainWindow::httpReadyRead()
{
    //if(logFile.isOpen())
        //logFile.write(m_reply->readAll());
    log_str.append(m_reply->readAll());
}

void MainWindow::clearAllExceptCityArea()
{
    ui->lineEdit_Name->clear();
    ui->lineEdit_CellPhone->clear();
    ui->lineEdit_HomePhone->clear();
    ui->lineEdit_Email->clear();
    ui->radioButton->setChecked(true);
    emit ui->radioButton->toggle();
    ui->lineEdit_PS->clear();
    ui->lineEdit_Name->setFocus();
}


void MainWindow::about()
{

    QString title = QStringLiteral("<b>島國機關槍 Lite ");
    QString version = QString(" ver. ") + TMMG_VERSION
#ifdef TEST_ON_MY_FORM
            + QStringLiteral(" 測試版")
#endif
            + "</b><br><br>";

    QString copy_right = QStringLiteral("Copyright© 2015 Raymond Liu. All right reserved<br>For technical support, mail to raymond770710@gmail.com");
    QMessageBox::information( this, QStringLiteral("關於 島國機關槍 Lite"), title + version + copy_right);
}

void MainWindow::readMe()
{
    QDialog dlg;
    QPlainTextEdit textEdit;
    QFile file(":/ReadMe.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text)) 
    {
        QMessageBox::warning(this, tr("Application"),
                            tr("Cannot read file %1:\n%2.")
                            .arg("ReadMe.txt")
                            .arg(file.errorString()));
        return;
    }
    textEdit.setPlainText(file.readAll());

    textEdit.setStyleSheet("font: 12pt");

    QVBoxLayout mainLayout;
    mainLayout.addWidget(&textEdit);
    dlg.setWindowTitle("Read me");
    dlg.setGeometry(50, 50, 1000, 700);
    dlg.setLayout(&mainLayout);
    dlg.exec();
}

void MainWindow::setLabelNumText(int num)
{
//    QString strText = QStringLiteral("本輪擊發次數：");
//    QString strColor = "#ff0000";
//    QString strNum = QString::number(num);
//    QString str = "<html><head/><body><p>" + strText +
//                  "<span style="" font-size:12pt; font-weight:600; color:#ff0000;"">" + strNum +
//                  "</span></p></body></html>";

    ui->label_num->setText(QString::number(num));
}
