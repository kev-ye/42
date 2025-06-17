#!/usr/bin/python3

from elem import Elem, Text
from elements import (Html, Head, Body, Title, Meta, Img, Table, Th, Tr, Td,
                     Ul, Ol, Li, H1, H2, P, Div, Span, Hr, Br)


class Page:
    def __init__(self, root):
        if not isinstance(root, Elem):
            raise TypeError("Root must be an instance of Elem")
        self.root = root

    def is_valid(self):
        return self._validate_node(self.root)

    def _validate_node(self, node):
        valid_types = (Html, Head, Body, Title, Meta, Img, Table, Th, Tr, Td,
                      Ul, Ol, Li, H1, H2, P, Div, Span, Hr, Br, Text)
        if not isinstance(node, valid_types):
            return False

        if isinstance(node, Html):
            if len(node.content) != 2:
                return False
            if not isinstance(node.content[0], Head) or not isinstance(node.content[1], Body):
                return False

    
        elif isinstance(node, Head):
            if node.content:
                if len(node.content) != 1 or not isinstance(node.content[0], Title):
                    return False

        elif isinstance(node, (Body, Div)):
            valid_content = (H1, H2, Div, Table, Ul, Ol, Span, Text)
            if node.content and not all(isinstance(child, valid_content) for child in node.content):
                return False

        elif isinstance(node, (Title, H1, H2, Li, Th, Td)):
            if node.content:
                if len(node.content) != 1 or not isinstance(node.content[0], Text):
                    return False

        elif isinstance(node, P):
            if node.content and not all(isinstance(child, Text) for child in node.content):
                return False

        elif isinstance(node, Span):
            if node.content and not all(isinstance(child, (Text, P)) for child in node.content):
                return False

        elif isinstance(node, (Ul, Ol)):
            if not node.content or not all(isinstance(child, Li) for child in node.content):
                return False

        elif isinstance(node, Tr):
            if not node.content or not all(isinstance(child, (Th, Td)) for child in node.content):
                return False
            has_th = any(isinstance(child, Th) for child in node.content)
            has_td = any(isinstance(child, Td) for child in node.content)
            if has_th and has_td:
                return False

        elif isinstance(node, Table):
            if node.content and not all(isinstance(child, Tr) for child in node.content):
                return False

        elif isinstance(node, Img):
            if node.content:  
                return False

        # Recursive check child node
        if hasattr(node, 'content'):
            for child in node.content:
                if not self._validate_node(child):
                    return False

        return True

    def __str__(self):
        result = ""
        if isinstance(self.root, Html):
            result = "<!DOCTYPE html>\n"
        result += str(self.root)
        return result

    def write_to_file(self, filename):
        with open(filename, 'w') as f:
            f.write(str(self))


if __name__ == '__main__':
    print("=== Test Basic HTML Structure valid ===")
    basic_html = Html([
        Head([
            Title(Text("Hello ground!"))
        ]),
        Body([
            H1(Text("Oh no, not again!"))
        ])
    ])
    page = Page(basic_html)
    print("Basic HTML structure is valid:", page.is_valid(), " == True")
    print("\nGenerated Basic HTML Structure:")
    print(page)

    print("=== Test Basic HTML Structure not valid ===")
    basic_html = Html([
        Head([
            Title(Text("Hello ground!"))
        ]),
        Body([
            H1(Text("Oh no, not again!")),
            Img({'src': 'http://i.imgur.com/pfp3T.jpg'})
        ])
    ])
    page = Page(basic_html)
    print("Basic HTML structure is valid:", page.is_valid(), " == False (Bcz Img in Body)")

    print("\n=== Test Empty Nodes ===")
    empty_html = Html([
        Head(),
        Body([
            H1(),
            Div(),
            P(),
            Span()
        ])
    ])
    page = Page(empty_html)
    print("Empty nodes structure is valid:", page.is_valid(), " == False (Bcz P in body)")

    print("\n=== Test List Structure ===")
    valid_list = Ul([
        Li(Text("Item 1")),
        Li(Text("Item 2")),
        Li(Text("Item 3"))
    ])
    page = Page(valid_list)
    print("Valid list structure is valid:", page.is_valid(), " == True")
    print("\nGenerated valid list:")
    print(page)

    empty_list = Ul([])
    page = Page(empty_list)
    print("\nEmpty list structure is valid:", page.is_valid(), " == False (Bcz Ul must have aleast one Li)")

    invalid_list = Ul([
        Li(Text("Item 1")),
        Div(Text("Invalid"))
    ])
    page = Page(invalid_list)
    print("Invalid list content is valid:", page.is_valid(), " == False (Bcz Ul only accept Li)")

    print("\n=== Test Table Structure ===")
    valid_table_th = Table([
        Tr([
            Th(Text("Header 1")),
            Th(Text("Header 2"))
        ])
    ])
    page = Page(valid_table_th)
    print("Table with only Th is valid:", page.is_valid(), " == True")
    print("\nGenerated table with Th:")
    print(page)

    valid_table_td = Table([
        Tr([
            Td(Text("Cell 1")),
            Td(Text("Cell 2"))
        ])
    ])
    page = Page(valid_table_td)
    print("\nTable with only Td is valid:", page.is_valid(), " == True")
    print("\nGenerated table with Td:")
    print(page)

    invalid_table_mixed = Table([
        Tr([
            Th(Text("Header")),
            Td(Text("Cell"))
        ])
    ])
    page = Page(invalid_table_mixed)
    print("\nMixed Th and Td is valid:", page.is_valid(), " == False (Bcz Th and Td cannot be exist in same time)")

    empty_tr = Table([
        Tr([])
    ])
    page = Page(empty_tr)
    print("\nEmpty Tr is valid:", page.is_valid(), " == False (Bcz Tr must have aleast one th/tr)")

    empty_table = Table([])
    page = Page(empty_table)
    print("\nEmpty Table is valid:", page.is_valid(), " == True")

    print("\n=== Test Complex Structure ===")
    complex_html = Html([
        Head([
            Title(Text("Complex Page"))
        ]),
        Body([
            H1(Text("Main Title")),
            Div([
                H2(Text("Subtitle")),
                Span([
                    P([
                        Text("This is a ")
                    ]),
                    Text(" Simple text.")
                ]),
                Ul([
                    Li(Text("List item 1")),
                    Li(Text("List item 2"))
                ]),
                Table([
                    Tr([
                        Th(Text("Header 1")),
                        Th(Text("Header 2"))
                    ]),
                    Tr([
                        Td(Text("Data 1")),
                        Td(Text("Data 2"))
                    ])
                ])
            ])
        ])
    ])
    page = Page(complex_html)
    print("Complex structure is valid:", page.is_valid(), " == True")
    print("\nGenerated complex structure:")
    print(page)

    print("\n=== Test File Writing ===")
    page = Page(basic_html)
    page.write_to_file("test.html")
    print("HTML file has been written to test.html") 