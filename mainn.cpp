
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <QVector>

struct Flight {
    QString flightNo;       // 편명 (예: LJ302)
    QString destination;    // 목적지/출발지 (예: GMP (김포))
    QString airline;        // 항공사 (예: 진에어)
    QString duration;       // 소요 시간 (예: 1시간 0분)
    int price;              // 가격 (예: 85000)
};

struct AirportNode {
    QString name;           // 공항명 (예: 제주 (CJU))
    QVector<Flight> dFlights; // 출발 항공편 (Departures)
    QVector<Flight> aFlights; // 도착 항공편 (Arrivals)
};

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("항공권 조회 및 예매 프로그램");
        resize(850, 550);
        
        setupGraph();
        setupUI();
        loadAirportList();
    }

private:
    QVector<AirportNode> graph;
    QWidget *centralWidget;
    
    QLabel *currentAirportLabel;
    QListWidget *airportListWidget;
    QListWidget *departListWidget;
    QListWidget *arriveListWidget;
    QPushButton *bookButton;

    void setupGraph() {
        // 이미지 속 '제주(CJU)' 기준 예시 데이터 세팅
        AirportNode jeju;
        jeju.name = "제주 (CJU)";
        // 출발 항공편
        jeju.dFlights.append({"LJ302", "GMP (김포)", "진에어", "1시간 0분", 85000});
        jeju.dFlights.append({"LJ502", "PUS (부산)", "진에어", "0시간 50분", 75000});
        // 도착 항공편
        jeju.aFlights.append({"LJ301", "GMP (김포)", "진에어", "1시간 0분", 80000});
        jeju.aFlights.append({"LJ501", "PUS (부산)", "진에어", "0시간 50분", 70000});

        // 다른 노드들 샘플 등록
        AirportNode gmp; gmp.name = "GMP (김포)";
        AirportNode pus; pus.name = "PUS (부산)";
        AirportNode lax; lax.name = "LAX (로스앤젤레스)";
        AirportNode jfk; jfk.name = "JFK (뉴욕)";

        graph.append(jeju);
        graph.append(gmp);
        graph.append(pus);
        graph.append(lax);
        graph.append(jfk);
    }

    void setupUI() {
        centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

        // 1. 왼쪽: 출발 공항(노드) 리스트
        QVBoxLayout *leftLayout = new QVBoxLayout();
        QLabel *titleLeft = new QLabel("공항 노드 선택");
        titleLeft->setStyleSheet("font-weight: bold; font-size: 14px;");
        airportListWidget = new QListWidget();
        
        leftLayout->addWidget(titleLeft);
        leftLayout->addWidget(airportListWidget);

        // 2. 오른쪽: 선택된 공항의 항공편 상세 정보 (이미지 우측 구조 반영)
        QVBoxLayout *rightLayout = new QVBoxLayout();
        
        currentAirportLabel = new QLabel("공항을 선택하세요.");
        currentAirportLabel->setStyleSheet("font-weight: bold; font-size: 16px; color: #111111;");
        
        QLabel *lblDepart = new QLabel("▶ 출발 항공편");
        lblDepart->setStyleSheet("font-weight: bold; color: blue;");
        departListWidget = new QListWidget();
        
        QLabel *lblArrive = new QLabel("▣ 도착 항공편");
        lblArrive->setStyleSheet("font-weight: bold; color: darkgreen;");
        arriveListWidget = new QListWidget();

        bookButton = new QPushButton("선택한 항공편 예매하기");

        rightLayout->addWidget(currentAirportLabel);
        rightLayout->addWidget(lblDepart);
        rightLayout->addWidget(departListWidget);
        rightLayout->addWidget(lblArrive);
        rightLayout->addWidget(arriveListWidget);
        rightLayout->addWidget(bookButton);

        // 전체 레이아웃 비율 설정 (좌측 3 : 우측 7)
        mainLayout->addLayout(leftLayout, 3);
        mainLayout->addLayout(rightLayout, 7);

        // 시그널-슬롯 연결
        connect(airportListWidget, &QListWidget::itemClicked, this, &MainWindow::showFlights);
        connect(bookButton, &QPushButton::clicked, this, &MainWindow::bookFlight);
    }

    void loadAirportList() {
        for (const auto &airport : graph) {
            airportListWidget->addItem(airport.name);
        }
    }

    void showFlights() {
        departListWidget->clear();
        arriveListWidget->clear();

        int idx = airportListWidget->currentRow();
        if (idx < 0 || idx >= graph.size()) return;

        const AirportNode &selected = graph[idx];
        currentAirportLabel->setText(selected.name);

        // 출발 항공편 채우기
        if (selected.dFlights.isEmpty()) {
            departListWidget->addItem("출발 항공편이 없습니다.");
        } else {
            for (const auto &f : selected.dFlights) {
                QString text = QString("[%1] %2 → %3  |  ₩%4  |  %5")
                               .arg(f.flightNo).arg(f.airline).arg(f.destination).arg(f.price).arg(f.duration);
                QListWidgetItem *item = new QListWidgetItem(text);
                item->setData(Qt::UserRole, idx);       // 선택한 공항 인덱스 저장
                item->setData(Qt::UserRole + 1, "D");   // 출발 표시
                departListWidget->addItem(item);
            }
        }

        // 도착 항공편 채우기
        if (selected.aFlights.isEmpty()) {
            arriveListWidget->addItem("도착 항공편이 없습니다.");
        } else {
            for (const auto &f : selected.aFlights) {
                QString text = QString("[%1] %2 ← %3  |  ₩%4  |  %5")
                               .arg(f.flightNo).arg(f.airline).arg(f.destination).arg(f.price).arg(f.duration);
                QListWidgetItem *item = new QListWidgetItem(text);
                item->setData(Qt::UserRole, idx);       // 선택한 공항 인덱스 저장
                item->setData(Qt::UserRole + 1, "A");   // 도착 표시
                arriveListWidget->addItem(item);
            }
        }
    }

    void bookFlight() {
        QListWidget *targetWidget = nullptr;

        // 활성화된 리스트 확인
        if (departListWidget->currentItem() && departListWidget->currentItem()->isSelected()) {
            targetWidget = departListWidget;
        } else if (arriveListWidget->currentItem() && arriveListWidget->currentItem()->isSelected()) {
            targetWidget = arriveListWidget;
        }

        if (!targetWidget || targetWidget->currentItem()->text().contains("없습니다")) {
            QMessageBox::warning(this, "경고", "예매할 항공편을 선택해 주세요.");
            return;
        }

        QListWidgetItem *item = targetWidget->currentItem();
        int airportIdx = item->data(Qt::UserRole).toInt();
        QString type = item->data(Qt::UserRole + 1).toString();
        int row = targetWidget->currentRow();

        AirportNode currentAirport = graph[airportIdx];
        Flight f = (type == "D") ? currentAirport.dFlights[row] : currentAirport.aFlights[row];

        // 이미지 우측 하단 메세지 규격에 맞춤 설정
        QString currentBaseName = currentAirport.name.split(" ")[0]; // "제주"
        QString destBaseName = f.destination.split(" ")[0];

        QString route = (type == "D") 
                        ? QString("%1 → %2").arg(currentBaseName).arg(destBaseName)
                        : QString("%1 → %2").arg(destBaseName).arg(currentBaseName);

        QString infoMessage = QString(
            "예매가 완료되었습니다.\n\n"
            "항공편: %1 (%2)\n"
            "구간: %3\n"
            "가격: ₩%4\n"
            "소요 시간: %5"
        ).arg(f.flightNo).arg(f.airline).arg(route).arg(f.price).arg(f.duration);

        QMessageBox::information(this, "예매 완료", infoMessage);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}