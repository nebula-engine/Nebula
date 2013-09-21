


namespace UI
{
    namespace Layout
    {
        /// Base
        class Base
        {
        public:
            /// Load XML
            void Load_XML(string);
            /// Render
            void Render(Platform::Renderer::Base*);
            
            /// Objects
            std::vector<UI::Object::Base::pointer> objects_;
        }
    }
}


