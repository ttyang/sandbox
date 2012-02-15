// Boost.Polygon library voronoi_visualizer.cpp file

//          Copyright Andrii Sydorchuk 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <iostream>
#include <set>
#include <vector>

#include <QtOpenGL/QGLWidget>
#include <QtGui/QtGui>

#include "boost/polygon/voronoi.hpp"
#include "boost/polygon/voronoi_utils.hpp"
using namespace boost::polygon;

class GLWidget : public QGLWidget {
  Q_OBJECT
public:
  GLWidget(QMainWindow *parent = NULL) :
      QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
      primary_edges_only_(false),
      internal_edges_only_(false) {
    startTimer(40);
  }

  QSize sizeHint() const {
    return QSize(600, 600);
  }

  void build(QString file_path) {
    ipoint_set_type point_sites;
    isegment_set_type segment_sites;

    // Open file.
    QFile data(file_path);
    if (!data.open(QFile::ReadOnly)) {
      QMessageBox::warning(this, tr("Voronoi Visualizer"),
                           tr("Disable to open file ") + file_path);
    }

    // Read points from the file.
    QTextStream in_stream(&data);
    int num_point_sites = 0;
    int num_edge_sites = 0;
    int x1, y1, x2, y2;
    in_stream >> num_point_sites;
    for (int i = 0; i < num_point_sites; ++i) {
      in_stream >> x1 >> y1;
      point_sites.push_back(ipoint_type(x1, y1));
    }
    in_stream >> num_edge_sites;
    for (int i = 0; i < num_edge_sites; ++i) {
      in_stream >> x1 >> y1 >> x2 >> y2;
      segment_sites.insert(isegment_type(ipoint_type(x1, y1),
                                         ipoint_type(x2, y2)));
    }
    in_stream.flush();

    // Build voronoi diagram.
    vd_.clear();
    construct_voronoi(point_sites, segment_sites, &vd_);
    brect_ = voronoi_utils<coordinate_type>::get_view_rectangle(
        vd_.bounding_rectangle(), 1.4);
    shift_ = point_data<double>((brect_.x_min() + brect_.x_max()) * 0.5,
                                (brect_.y_min() + brect_.y_max()) * 0.5);

    exterior_edges_set_.clear();
    for (voronoi_edge_const_iterator_type it = vd_.edge_records().begin();
        it != vd_.edge_records().end(); ++it) {
      if (!it->is_bounded()) {
        remove_exterior(&(*it));
      }
    }

    // Update view.
    update_view_port();
  }

  void show_primary_edges_only() {
    primary_edges_only_ ^= true;
  }

  void show_internal_edges_only() {
    internal_edges_only_ ^= true;
  }

protected:
  void initializeGL() {
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
  }

  void paintGL() {
    qglClearColor(QColor::fromRgb(255, 255, 255));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw voronoi sites.
    {
      const voronoi_cells_type &cells = vd_.cell_records();
      voronoi_cell_const_iterator_type it;
      glColor3f(0.0f, 0.5f, 1.0f);
      glPointSize(9);
      glBegin(GL_POINTS);
      for (it = cells.begin(); it != cells.end(); ++it) {
        if (!it->contains_segment()) {
          glVertex2f(it->point0().x() - shift_.x(),
                     it->point0().y() - shift_.y());
        }
      }
      glEnd();
      glPointSize(6);
      glLineWidth(2.7f);
      glBegin(GL_LINES);
      for (it = cells.begin(); it != cells.end(); ++it) {
        if (it->contains_segment()) {
          glVertex2f(it->point0().x() - shift_.x(),
                     it->point0().y() - shift_.y());
          glVertex2f(it->point1().x() - shift_.x(),
                     it->point1().y() - shift_.y());
        }
      }
      glEnd();
      glLineWidth(1.0);
    }

    //// Draw voronoi vertices.
    //{
    //  const voronoi_vertices_type &vertices = vd_.vertex_records();
    //  voronoi_vertex_const_iterator_type it;
    //  glColor3f(0.0f, 0.0f, 0.0f);
    //  glBegin(GL_POINTS);
    //  for (it = vertices.begin(); it != vertices.end(); ++it) {
    //    glVertex2f(it->vertex().x() - shift_.x(),
    //               it->vertex().y() - shift_.y());
    //  }
    //  glEnd();
    //}

    // Draw voronoi edges.
    {
      const voronoi_edges_type &edges = vd_.edge_records();
      voronoi_edge_const_iterator_type it;
      glColor3f(0.0f, 0.0f, 0.0f);
      glLineWidth(1.7f);
      glBegin(GL_LINES);
      for (it = edges.begin(); it != edges.end(); ++it) {
        if (primary_edges_only_ && !it->is_primary()) {
          continue;
        }
        if (internal_edges_only_ && exterior_edges_set_.count(&(*it))) {
          continue;
        }
        std::vector<opoint_type> temp_v =
          voronoi_utils<coordinate_type>::get_point_interpolation(
              &(*it), brect_, 1E-3);
        for (int i = 0; i < static_cast<int>(temp_v.size()) - 1; ++i) {
          glVertex2f(temp_v[i].x() - shift_.x(), temp_v[i].y() - shift_.y());
          glVertex2f(temp_v[i+1].x() - shift_.x(), temp_v[i+1].y() - shift_.y());
        }
      }
      glEnd();
    }
  }

  void resizeGL(int width, int height) {
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
  }

  void timerEvent(QTimerEvent *) {
    update();
  }

private:
  void remove_exterior(const voronoi_diagram<double>::voronoi_edge_type* edge) {
    if (exterior_edges_set_.count(edge)) {
      return;
    }
    exterior_edges_set_.insert(edge);
    exterior_edges_set_.insert(edge->twin());
    const voronoi_diagram<double>::voronoi_vertex_type* v = edge->vertex1();
    if (v == NULL || !edge->is_primary()) {
      return;
    }
    const voronoi_diagram<double>::voronoi_edge_type* e = v->incident_edge();
    do {
      remove_exterior(e);
      e = e->rot_next();
    } while (e != v->incident_edge());
  }

  void update_view_port() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(brect_.x_min() - shift_.x(), brect_.x_max() - shift_.x(),
            brect_.y_min() - shift_.y(), brect_.y_max() - shift_.y(),
            -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
  }

  typedef double coordinate_type;
  typedef point_data<int> ipoint_type;
  typedef point_data<double> opoint_type;
  typedef directed_line_segment_data<int> isegment_type;
  typedef std::vector<ipoint_type> ipoint_set_type;
  typedef directed_line_segment_set_data<int> isegment_set_type;
  typedef voronoi_diagram<coordinate_type>::voronoi_edge_type
    voronoi_edge_type;
  typedef voronoi_diagram<coordinate_type>::voronoi_cells_type
    voronoi_cells_type;
  typedef voronoi_diagram<coordinate_type>::voronoi_vertices_type
    voronoi_vertices_type;
  typedef voronoi_diagram<coordinate_type>::voronoi_edges_type
    voronoi_edges_type;
  typedef voronoi_diagram<coordinate_type>::voronoi_cell_const_iterator_type
    voronoi_cell_const_iterator_type;
  typedef voronoi_diagram<coordinate_type>::voronoi_vertex_const_iterator_type
    voronoi_vertex_const_iterator_type;
  typedef voronoi_diagram<coordinate_type>::voronoi_edge_const_iterator_type
    voronoi_edge_const_iterator_type;
  bounding_rectangle<coordinate_type> brect_;
  point_data<double> shift_;
  voronoi_diagram<coordinate_type> vd_;
  std::set<const voronoi_edge_type*> exterior_edges_set_;
  bool primary_edges_only_;
  bool internal_edges_only_;
};

class MainWindow : public QWidget {
  Q_OBJECT
public:
  MainWindow() {
    glWidget_ = new GLWidget();
    file_dir_ = QDir(QDir::currentPath(), tr("*.txt"));
    file_name_ = tr("");

    QHBoxLayout *centralLayout = new QHBoxLayout;
    centralLayout->addWidget(glWidget_);
    centralLayout->addLayout(create_file_layout());
    setLayout(centralLayout);

    update_file_list();
    setWindowTitle(tr("Voronoi Visualizer"));
    layout()->setSizeConstraint(QLayout::SetFixedSize);
  }

private slots:
  void primary_edges_only() {
    glWidget_->show_primary_edges_only();
  }

  void internal_edges_only() {
    glWidget_->show_internal_edges_only();
  }

  void browse() {
    QString new_path = QFileDialog::getExistingDirectory(
        0, tr("Choose Directory"), file_dir_.absolutePath());
    if (new_path.isEmpty()) {
      return;
    }
    file_dir_.setPath(new_path);
    update_file_list();
  }

  void build() {
    file_name_ = file_list_->currentItem()->text();
    QString file_path = file_dir_.filePath(file_name_);
    message_label_->setText("Building...");
    glWidget_->build(file_path);
    message_label_->setText("Double click the item to build voronoi diagram:");
    setWindowTitle(tr("Voronoi Visualizer - ") + file_path);
  }

  void print_scr() {
    if (!file_name_.isEmpty()) {
      QImage screenshot = glWidget_->grabFrameBuffer(true);
      QString output_file = file_dir_.absolutePath() + tr("/") +
          file_name_.left(file_name_.indexOf('.')) + tr(".png");
      screenshot.save(output_file, 0, -1);
    }
  }

private:
  QGridLayout *create_file_layout() {
    QGridLayout *file_layout = new QGridLayout;

    message_label_ = new QLabel("Double click item to build voronoi diagram:");

    file_list_ = new QListWidget();
    file_list_->connect(file_list_,
                        SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                        this,
                        SLOT(build()));

    QCheckBox *primary_checkbox = new QCheckBox("Show primary edges only.");
    connect(primary_checkbox, SIGNAL(clicked()),
        this, SLOT(primary_edges_only()));

    QCheckBox *internal_checkbox = new QCheckBox("Show internal edges only.");
    connect(internal_checkbox, SIGNAL(clicked()),
        this, SLOT(internal_edges_only()));

    QPushButton *browse_button =
        new QPushButton(tr("Browse Input Directory"));
    connect(browse_button, SIGNAL(clicked()), this, SLOT(browse()));
    browse_button->setMinimumHeight(50);

    QPushButton *print_scr_button = new QPushButton(tr("Make Screenshot"));
    connect(print_scr_button, SIGNAL(clicked()), this, SLOT(print_scr()));
    print_scr_button->setMinimumHeight(50);

    file_layout->addWidget(message_label_, 0, 0);
    file_layout->addWidget(file_list_, 1, 0);
    file_layout->addWidget(primary_checkbox, 2, 0);
    file_layout->addWidget(internal_checkbox, 3, 0);
    file_layout->addWidget(browse_button, 4, 0);
    file_layout->addWidget(print_scr_button, 5, 0);

    return file_layout;
  }

  void update_file_list() {
    QFileInfoList list = file_dir_.entryInfoList();
    file_list_->clear();
    if (file_dir_.count() == 0) {
      return;
    }
    QFileInfoList::const_iterator it;
    for (it = list.begin(); it != list.end(); it++) {
      file_list_->addItem(it->fileName());
    }
    file_list_->setCurrentRow(0);
  }

  QDir file_dir_;
  QString file_name_;
  GLWidget *glWidget_;
  QListWidget *file_list_;
  QLabel *message_label_;
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow window;
  window.show();
  return app.exec();
}

#include "voronoi_visualizer.moc"
