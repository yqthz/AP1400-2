#ifndef Q4_H
#define Q4_H
namespace q4 {
    struct Vector2D {
        double x{};
        double y{};
        Vector2D(double x, double y) : x(x), y(y) { }
    };

    struct Sensor {
        Vector2D pos;
        double accuracy;
    };

    inline Vector2D kalman_filter(std::vector<Sensor>& sensors) {
        double sum = 0;
        for (size_t i = 0; i < sensors.size(); i++) {
            sum += sensors[i].accuracy;
        }
        std::vector<double> weights;
        for (size_t i = 0; i < sensors.size(); i++) {
            weights.push_back(sensors[i].accuracy / sum);
        }
        double x = 0, y = 0;
        size_t t = 0;
        for (size_t i = 0; i < sensors.size(); i++) {
            x += weights[i] * sensors[i].pos.x;
            y += weights[i] * sensors[i].pos.y;
            t++;
        }

        return Vector2D(x, y);
        
    }

}

#endif //Q4_H