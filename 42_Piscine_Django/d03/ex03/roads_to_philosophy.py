import sys
import requests
from bs4 import BeautifulSoup


def get_page_content(title):
    url = f"https://en.wikipedia.org/wiki/{title.replace(' ', '_')}"
    headers = {
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36'
    }
    
    try:
        response = requests.get(url, headers=headers, timeout=10)
        response.raise_for_status()
        soup = BeautifulSoup(response.text, 'html.parser')

        title_elem = soup.find('h1', class_='firstHeading')
        if not title_elem:
            return None
        
        actual_title = title_elem.get_text()
        return soup, actual_title
    except Exception:
        return None


def find_first_valid_link(soup):
    content = soup.find('div', id='mw-content-text')
    if not content:
        return None
    
    def check_link(link):
        attrs = link.attrs

        attr_keys = set(attrs.keys())
        if not attr_keys.issubset({'href', 'title'}):
            return None

        if 'href' not in attrs:
            return None
        
        href = attrs['href']

        if not href.startswith('/wiki/'):
            return None

        if 'title' in attrs:
            title = attrs['title']
            if ':' in title:
                return None
    
        article_name = href[6:]
        return article_name

    for paragraph in content.find_all('p'):
        for link in paragraph.find_all('a'):
            result = check_link(link)
            if result:
                return result
    for ul in content.find_all('ul'):
        for li in ul.find_all('li'):
            for link in li.find_all('a'):
                result = check_link(link)
                if result:
                    return result 
    return None


def roads_to_philosophy(start_title):
    visited = []
    current_title = start_title
    
    while True:
        # Fetch the page
        result = get_page_content(current_title)
        if not result:
            print("It leads to a dead end!")
            return
        
        soup, actual_title = result
        if actual_title == "Philosophy":
            print(actual_title)
            visited.append(actual_title)
            count = len(visited)
            print(f"{count} roads from {start_title} to philosophy!")
            return
        if actual_title in visited:
            print("It leads to an infinite loop!")
            return
        print(actual_title)
        visited.append(actual_title)
        next_link = find_first_valid_link(soup)
        
        if not next_link:
            print("It leads to a dead end!")
            return
        current_title = next_link


def main():
    """Handle command line arguments and start the process."""
    if len(sys.argv) != 2:
        print("Error: Invalid number of arguments.")
        print("Usage: python3 roads_to_philosophy.py \"search term\"")
        return
    
    query = sys.argv[1]
    
    if not query or query.strip() == "":
        print("Error: Search term cannot be empty.")
        return
    
    roads_to_philosophy(query)


if __name__ == '__main__':
    main()
