def create_element_table_html():
    html = ""
    for element_dict in generate_element():
        if element_dict['position'] == '0':
            html += f"<tr>{element_info_html(element_dict)}"
            previous_pos = 0
        else:
            if previous_pos + 1 < (current_pos := int(element_dict['position'])):
                for _ in range(current_pos - previous_pos - 1):
                        html += f"<td></td>"
            previous_pos = current_pos
            html += f"{element_info_html(element_dict)}"
            if element_dict['position'] == '17':
                html += "</tr>"
            
    return html
            


def element_info_html(element: dict | None):
    return f"""
        <td style="border: 1px solid black; padding:10px">
            <h4>{element['name']}</h4>
            <ul>
                <li>No {element['number']}</li>
                <li>{element['small']}</li>
                <li>{element['molar']}</li>
                <li>{sum([int(e) for e in element['electron'].split(' ')])} electron</li>
            </ul>
        </td>
    """ if element else "<td></td>"


def line_info_to_dict(line: str) -> dict:
    element_dict = {}
    for i, data in enumerate(line.split(',')):
        if i == 0:
            sub_data = data.split('=')
            sub_data_2 = sub_data[1].split(':')
            element_dict['name'] = sub_data[0].strip()
            element_dict[sub_data_2[0].strip()] = sub_data_2[1].strip()
        else:
            sub_data = data.split(':')
            element_dict[sub_data[0].strip()] = sub_data[1].strip()
    return element_dict


def generate_element():
    with open('periodic_table.txt', 'r') as f:
        for line in f.readlines():
            yield line_info_to_dict(line)


def periodic_table():
    html_base = f"""
    <!DOCTYPE html>
    <html lang="en">
    <head>
    <meta charset="utf-8">
    <title>Table of the elements</title>
    </head>
    <body>
    <table>
        {create_element_table_html()}
    </table>
    </body>
    </html>
    """
    with open('periodic_table.html', 'w') as f:
        f.write(html_base)


if __name__ == '__main__':
    periodic_table()