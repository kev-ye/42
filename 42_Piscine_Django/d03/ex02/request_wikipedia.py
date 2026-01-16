import sys
import requests
import dewiki


def search_wikipedia(query):
    api_url = "https://fr.wikipedia.org/w/api.php"
    headers = {
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36'
    }
    
    params = {
        'action': 'query',
        'format': 'json',
        'titles': query,
        'prop': 'revisions',
        'rvprop': 'content',
        'rvslots': 'main',
        'redirects': 1
    }

    try:
        response = requests.get(api_url, params=params, headers=headers, timeout=10)
        response.raise_for_status()
        data = response.json()

        print(data)
        
        pages = data.get('query', {}).get('pages', {})
        if not pages:
            print("Error: Could not retrieve page content.")
            return None

        page_id = list(pages.keys())[0]
        if page_id == '-1':
            print("Error: Page not found.")
            return None
        
        page = pages[page_id]
        revisions = page.get('revisions', [])
        if not revisions:
            print("Error: No content found.")
            return None
            
        page_content = revisions[0].get('slots', {}).get('main', {}).get('*', '')
        
        if not page_content:
            print("Error: Page content is empty.")
            return None

        return dewiki.from_string(page_content)
    except Exception as e:
        print(f"Error: An unexpected error occurred: {e}")
        return None


def create_filename(title):
    filename = title.replace(' ', '_')
    filename = ''.join(c for c in filename if c.isalnum() or c in ('_', '-'))
    return f"{filename}.wiki"


def main():
    if len(sys.argv) != 2:
        print("Error: Invalid number of arguments.")
        print("Usage: python3 request_wikipedia.py \"search term\"")
        return
    
    query = sys.argv[1]
    
    if not query or query.strip() == "":
        print("Error: Search term cannot be empty.")
        return

    if not (result := search_wikipedia(query)):
        return

    filename = create_filename(query)
    try:
        with open(filename, 'w', encoding='utf-8') as f:
            f.write(result)
    except Exception as e:
        print(f"Error: An unexpected error occurred while writing to file: {e}")


if __name__ == '__main__':
    main()
