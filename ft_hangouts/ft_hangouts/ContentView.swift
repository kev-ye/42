import SwiftUI

struct ContentView: View {
    @EnvironmentObject var appState: AppState
    
    var body: some View {
        ZStack {
            if appState.currentUser == nil {
                LoginView()
            } else {
                MainTabView()
            }
            
            if appState.showBackgroundToast {
                VStack {
                    Spacer()
                    Text(appState.backgroundMessage)
                        .padding()
                        .background(Color.black.opacity(0.8))
                        .foregroundColor(.white)
                        .cornerRadius(10)
                        .padding()
                }
                .transition(.move(edge: .bottom))
                .animation(.easeInOut, value: appState.showBackgroundToast)
            }
        }
    }
}
