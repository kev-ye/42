#!/usr/bin/python3

from elem import Elem, Text


class Html(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='html', attr=attr, content=content)


class Head(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='head', attr=attr, content=content)


class Body(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='body', attr=attr, content=content)


class Title(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='title', attr=attr, content=content)


class Meta(Elem):
    def __init__(self, attr={}):
        super().__init__(tag='meta', attr=attr, tag_type='simple')


class Img(Elem):
    def __init__(self, attr={}):
        super().__init__(tag='img', attr=attr, tag_type='simple')


class Table(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='table', attr=attr, content=content)


class Th(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='th', attr=attr, content=content)


class Tr(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='tr', attr=attr, content=content)


class Td(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='td', attr=attr, content=content)


class Ul(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='ul', attr=attr, content=content)


class Ol(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='ol', attr=attr, content=content)


class Li(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='li', attr=attr, content=content)


class H1(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='h1', attr=attr, content=content)


class H2(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='h2', attr=attr, content=content)


class P(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='p', attr=attr, content=content)


class Div(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='div', attr=attr, content=content)


class Span(Elem):
    def __init__(self, content=None, attr={}):
        super().__init__(tag='span', attr=attr, content=content)


class Hr(Elem):
    def __init__(self, attr={}):
        super().__init__(tag='hr', attr=attr, tag_type='simple')


class Br(Elem):
    def __init__(self, attr={}):
        super().__init__(tag='br', attr=attr, tag_type='simple')


if __name__ == '__main__':
    print("\n=== Simple test ===")
    print( Html( [Head(), Body()] ) )

    html = Html([
        Head([
            Title(Text("Hello ground!"))
        ]),
        Body([
            H1(Text("Oh no, not again!")),
            Img({'src': 'http://i.imgur.com/pfp3T.jpg'})
        ])
    ])
    print('\n')
    print(html)

    print("\n=== Other test ===")
    table = Table([
        Tr([
            Th(Text("Header 1")),
            Th(Text("Header 2"))
        ]),
        Tr([
            Td(Text("Cell 1")),
            Td(Text("Cell 2"))
        ])
    ])
    print("\n1:")
    print(table)

    # 测试列表
    ul = Ul([
        Li(Text("Item 1")),
        Li(Text("Item 2")),
        Li(Text("Item 3"))
    ])
    print("\n2:")
    print(ul)

    ol = Ol([
        Li(Text("First")),
        Li(Text("Second")),
        Li(Text("Third"))
    ])
    print("\n3:")
    print(ol)

    # 测试段落和文本样式
    div = Div([
        P(Text("This is a paragraph.")),
        Span(Text("This is a span.")),
        Hr(),
        Br()
    ])
    print("\n4:")
    print(div) 