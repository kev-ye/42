#!/usr/bin/python3


class Text(str):
    """
    A Text class to represent a text you could use with your HTML elements.

    Because directly using str class was too mainstream.
    """

    def __str__(self):
        """
        Do you really need a comment to understand this method?..
        """
        text = super().__str__()
        text = text.replace('&', '&amp;')
        text = text.replace('<', '&lt;')
        text = text.replace('>', '&gt;')
        text = text.replace('"', '&quot;')
        text = text.replace("'", '&apos;')
        text = text.replace('\n', '\n<br />\n')
        return text


class Elem:
    """
    Elem will permit us to represent our HTML elements.
    """
    class ValidationError(Exception):
        def __init__(self):
            super().__init__("Content must be a string or an Elem instance.")

    def __init__(self, tag='div', attr={}, content=None, tag_type='double'):
        """
        __init__() method.

        Obviously.
        """
        self.tag = tag
        self.attr = attr
        self.content = []
        self.tag_type = tag_type

        if content is not None:
            self.add_content(content)

    def __str__(self):
        """
        The __str__() method will permit us to make a plain HTML representation
        of our elements.
        Make sure it renders everything (tag, attributes, embedded
        elements...).
        """
        result = f'<{self.tag}{self.__make_attr()}>'
        result += self.__make_content()
        if self.tag_type == 'double':
            result += f'</{self.tag}>'
        return result

    def __make_attr(self):
        """
        Here is a function to render our elements attributes.
        """
        result = ''
        for k, v in sorted(self.attr.items()):
            result += f' {str(k)}="{str(v)}"'
        return result

    def __make_content(self):
        """
        Here is a method to render the content, including embedded elements.
        """
        if len(self.content) == 0:
            return ''
        result = '\n'
        for elem in self.content:
            if isinstance(elem, Elem):
                result += '  ' + str(elem).replace('\n', '\n  ') + '\n'
            else:
                result += '  ' + str(elem) + '\n'
        return result

    def add_content(self, content):
        if not Elem.check_type(content):
            raise Elem.ValidationError
        if type(content) == list:
            self.content += [elem for elem in content if elem != Text('')]
        elif content != Text(''):
            self.content.append(content)

    @staticmethod
    def check_type(content):
        """
        Is this object a HTML-compatible Text instance or a Elem, or even a
        list of both?
        """
        if isinstance(content, Elem) or isinstance(content, Text):
            return True
        if type(content) == list:
            return all(isinstance(elem, (Elem, Text)) for elem in content)
        return False


if __name__ == '__main__':
    html = Elem('html')
    head = Elem('head')
    title = Elem('title', content=Text("Hello ground!"))
    body = Elem('body')
    h1 = Elem('h1', content=Text("Oh no, not again!"))
    img = Elem('img', {'src': 'http://i.imgur.com/pfp3T.jpg'}, tag_type='simple')

    head.add_content(title)
    body.add_content(h1)
    body.add_content(img)
    html.add_content(head)
    html.add_content(body)

    print(html)
