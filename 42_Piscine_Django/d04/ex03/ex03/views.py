from django.shortcuts import render


def index(request):
    """Display color gradient table."""
    # Generate 50 shades for each color (from light to dark)
    shades = []
    for i in range(50):
        # Calculate intensity (from 255 to 0 for gradient)
        intensity = int(255 - (i * 255 / 49))
        
        shades.append({
            'black': f'rgb({intensity}, {intensity}, {intensity})',
            'red': f'rgb(255, {intensity}, {intensity})',
            'blue': f'rgb({intensity}, {intensity}, 255)',
            'green': f'rgb({intensity}, 255, {intensity})',
        })
    
    colors = ['Black', 'Red', 'Blue', 'Green']
    
    return render(request, 'ex03/index.html', {
        'colors': colors,
        'shades': shades
    })
