#include <string>
#include <iostream>

class Text {
public:
   virtual void render(const std::string& data) const {
      std::cout << data;
   }

   virtual void render(const std::string& data_1, const std::string& data_2) const {
      std::cout << data_2;
   }
};

class DecoratedText : public Text {
public:
   explicit DecoratedText(Text* text) : text_(text) {}
   Text* text_;
};

class ItalicText : public DecoratedText {
public:
   explicit ItalicText(Text* text) : DecoratedText(text) {}
   void render(const std::string& data)  const {
      std::cout << "<i>";
      text_->render(data);
      std::cout << "</i>";
   }
};

class BoldText : public DecoratedText {
public:
   explicit BoldText(Text* text) : DecoratedText(text) {}
   void render(const std::string& data) const {
      std::cout << "<b>";
      text_->render(data);
      std::cout << "</b>";
   }
};

class Paragraph : public DecoratedText {
public:
   explicit Paragraph(Text* text) : DecoratedText(text) {}
   void render(const std::string& data) const {
      std::cout << "<p>";
      text_->render(data);
      std::cout << "</p>";
   }
};

class Reversed : public DecoratedText {
public:
   explicit Reversed(Text* text) : DecoratedText(text) {}
   void render(const std::string& data) const {
      std::string copy{ data };
      std::reverse(copy.begin(), copy.end());
      text_->render(copy);
   }
};

class Link : public DecoratedText {
public:
   explicit Link(Text* text) : DecoratedText(text) {}
   void render(const std::string& data_1, const std::string& data_2) const {
      std::cout << "<a href=" << data_1 << ">";
      text_->render(data_2);
      std::cout << "</a>";
   }
};

int main() {
   auto text_block = new ItalicText(new BoldText(new Text()));
   text_block->render("Hello world");

   auto text_block_1 = new Paragraph(new Text());
   text_block_1->render("Hello world");

   auto text_block_2 = new Reversed(new Text());
   text_block_2->render("Hello world");

   auto text_block_3 = new Link(new Text());
   text_block_3->render("netology.ru", "Hello world");
}