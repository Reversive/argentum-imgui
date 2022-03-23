#pragma once
namespace argentum {
   
    class c_ctx {
    private:
        void init_hooks() const;
    public:
        void run();
    };

    inline const auto g_ctx = std::make_unique< c_ctx >();
}