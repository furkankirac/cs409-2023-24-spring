// [[nodiscard]], std::unique_ptr, std::shared_ptr
// duck typing? type erasure: std::function
// SFINAE: enable_if, and its relation with concepts
// ADL: argument dependent lookup, friend functions
// CRTP: curiously recurring template pattern

#include <iostream>
#include <memory>

using namespace std;

[[nodiscard]] int foo() {
    return 1;
}

[[nodiscard]] unique_ptr<int> bar(unique_ptr<int> i)
{
    return std::move(i);
}


struct RGBPixel
{
    char r, g, b;
};

template<typename PixelType>
struct Image
{
    size_t height, width;

    PixelType* data;

    Image(size_t height, size_t width) : height{height}, width{width} {
        data = new PixelType[height * width];
    }

    ~Image() {
        delete[] data;
    }

};

auto createImage() {
//    auto* ptr = new Image<RGBPixel>(100, 100); // C way of doing it
//    return ptr;
    return make_shared<Image<RGBPixel>>(100, 100);
}

auto useImage(Image<RGBPixel> *)
{
}

template<typename T>
void edge_detect(shared_ptr<Image<T>> img)
{
}

int main()
{
//    auto* newImg = createImage();
//    delete newImg;

//    useImage(newImg);


//    auto img = std::shared_ptr<Image<RGBPixel>>(new Image<RGBPixel>(100, 100));
    auto img = make_shared<Image<RGBPixel>>(100, 100); // allocated the object automatically from heap
    edge_detect(img);

   // foo(); // this warns you so that the return value cannot be ignored

   // auto i_ptr = unique_ptr<int>(new int(10));
    // auto i_ptr = make_unique<int>(10);

   // cout << *i_ptr << endl;

   // auto i_ptr2 = std::move(i_ptr); // copy ctor is in "= delete" state
   // cout << i_ptr2 << endl;

   // auto j = bar(std::move(i_ptr2));


   auto s_ptr = shared_ptr<int>(new int(10));
   // auto s_ptr = make_shared<int>(10);

//    cout << *s_ptr << endl;

//    auto s_ptr2 = s_ptr; // happily copy construct
//    cout << *s_ptr << endl;
//    cout << *s_ptr2 << endl;

//    auto k = bar(std::move(i_ptr2));

}
