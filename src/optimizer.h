constexpr float default_beta1 = 0.9f;
constexpr float default_beta2 = 0.999f;
constexpr float default_epsilon = 0.00000001f;

class Adam_w {
public:
    float beta1;
    float beta2;
    float epsilon;

    Adam_w(float b1 = default_beta1, float b2 = default_beta2, float e = default_epsilon) : beta1(b1), beta2(b2), epsilon(e) {}

    void update(float& v, Gradient& grad, const float gradient_sum, const float learning_rate) {
        const float decay = 1.0f - 0.01f * learning_rate;
        v *= decay;
        grad.m = beta1 * grad.m + (1 - beta1) * gradient_sum;
        grad.v = beta2 * grad.v + (1 - beta2) * gradient_sum * gradient_sum;
        v -= learning_rate * grad.m / (sqrt(grad.v) + epsilon);
    }

    friend std::ostream& operator<<(std::ostream& os, const Adam_w& adam_w) {
        os << "Adam_w(" << "beta1=" << adam_w.beta1 << ", beta2=" << adam_w.beta2 << ", epsilon=" << adam_w.epsilon << ")";
        return os;
    }
};