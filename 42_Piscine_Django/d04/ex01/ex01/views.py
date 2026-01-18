from django.shortcuts import render


def django_page(request):
    """Display Django introduction page."""
    return render(request, 'ex01/django.html')


def affichage_page(request):
    """Display static page process explanation."""
    return render(request, 'ex01/affichage.html')


def templates_page(request):
    """Display template engine explanation."""
    return render(request, 'ex01/templates.html')
