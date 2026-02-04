import SwiftUI

class AppState: ObservableObject {
    @Published var currentUser: User?
    @Published var headerColor: Color = .blue
    @Published var showBackgroundToast = false
    @Published var backgroundMessage = ""
    
    private let backgroundTimeKey = "backgroundTime"
    
    init() {
        loadHeaderColor()
        loadCurrentUser()
    }
    
    func saveBackgroundTime() {
        UserDefaults.standard.set(Date(), forKey: backgroundTimeKey)
    }
    
    func checkBackgroundTime() {
        if let backgroundTime = UserDefaults.standard.object(forKey: backgroundTimeKey) as? Date {
            let formatter = DateFormatter()
            formatter.dateStyle = .medium
            formatter.timeStyle = .medium
            backgroundMessage = "last_background".localized + ": \(formatter.string(from: backgroundTime))"
            showBackgroundToast = true
            
            DispatchQueue.main.asyncAfter(deadline: .now() + 3) {
                self.showBackgroundToast = false
            }
        }
    }
    
    func loadHeaderColor() {
        if let colorData = UserDefaults.standard.data(forKey: "headerColor"),
           let color = try? JSONDecoder().decode(CodableColor.self, from: colorData) {
            headerColor = color.color
        }
    }
    
    func saveHeaderColor(_ color: Color) {
        headerColor = color
        if let colorData = try? JSONEncoder().encode(CodableColor(color: color)) {
            UserDefaults.standard.set(colorData, forKey: "headerColor")
        }
    }
    
    func loadCurrentUser() {
        if let phoneNumber = UserDefaults.standard.string(forKey: "currentUserPhone") {
            currentUser = DatabaseManager.shared.getOrCreateUser(phoneNumber: phoneNumber)
        }
    }
    
    func setCurrentUser(phoneNumber: String) {
        currentUser = DatabaseManager.shared.getOrCreateUser(phoneNumber: phoneNumber)
        UserDefaults.standard.set(phoneNumber, forKey: "currentUserPhone")
    }
    
    func logout() {
        currentUser = nil
        UserDefaults.standard.removeObject(forKey: "currentUserPhone")
    }
}

struct CodableColor: Codable {
    var red: Double
    var green: Double
    var blue: Double
    var opacity: Double
    
    var color: Color {
        Color(red: red, green: green, blue: blue, opacity: opacity)
    }
    
    init(color: Color) {
        let uiColor = UIColor(color)
        var r: CGFloat = 0, g: CGFloat = 0, b: CGFloat = 0, a: CGFloat = 0
        uiColor.getRed(&r, green: &g, blue: &b, alpha: &a)
        self.red = Double(r)
        self.green = Double(g)
        self.blue = Double(b)
        self.opacity = Double(a)
    }
}
