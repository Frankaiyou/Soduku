#ifndef THINGS_H
#define THINGS_H
#endif

class VIPModel : public QStandardItemModel {
    Q_OBJECT
public:
    VIPModel(QObject *parent=NULL) : QStandardItemModel(parent) { }
    VIPModel(int row, int column, QObject *parent=NULL)
        : QStandardItemModel(row, column, parent) { }
    QVariant data(const QModelIndex &index, int role) const {
        switch (role) {
            case Qt::DisplayRole:
                return QStandardItemModel::data(index, 0);
                break;
            case Qt::TextAlignmentRole:
                return Qt::AlignCenter;
                break;
            case Qt::CheckStateRole:

                break;

        default:
             return QVariant();
             break;
        }
        return QVariant();

    }

};

class Things {
public:
    QStandardItemModel* model;
    Soduku* M;
    QTimer* time;
    int BeginTime;
    Things() {
        model = new QStandardItemModel();
        M = new Soduku();
        time = new QTimer();
        BeginTime = 0;
    }
    void Init() {
        model->setColumnCount(9);
        model->setRowCount(9);
    }
};
