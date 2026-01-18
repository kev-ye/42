from django.shortcuts import render


def index(request):
    """Display Markdown cheatsheet page."""
    return render(request, 'ex00/index.html')
