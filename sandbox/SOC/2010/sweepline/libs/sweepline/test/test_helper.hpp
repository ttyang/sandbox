#include <iostream>
#include <fstream>

template <typename T>
void save_voronoi_input(const std::vector< point_data<T> > &points, const char *file_name) {
    std::ofstream ofs(file_name);
    ofs << points.size() << std::endl;
    for (int i = 0; i < (int)points.size(); ++i)
        ofs << points[i].x() << " " << points[i].y() << std::endl;
    ofs.close();
}

template <typename T>
void save_voronoi_input(const directed_line_segment_set_data<T> &segments, const char *file_name) {
    std::ofstream ofs(file_name);
    //ofs << segments.size() << std::endl;
    for (directed_line_segment_set_data<T>::iterator_type it = segments.begin();
         it != segments.end(); ++it) {
        ofs << it->low().x() << " " << it->low().y() << " ";
        ofs << it->high().x() << " " << it->high().y() << std::endl;
    }
    ofs.close();
}