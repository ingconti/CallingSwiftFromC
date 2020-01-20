//
//  ContentView.swift
//  CallingSwiftFromC
//
//  Created by ing.conti on 19/01/2020.
//  Copyright © 2020 ing.conti. All rights reserved.
//

// from https://forums.swift.org/t/best-way-to-call-a-swift-function-from-c/9829


import SwiftUI

// bad patch to allow refreshing UI...

fileprivate var buffer = ""

struct ContentView: View {
    @State private var selection = 0
    @State private var message = "here!"

    static func set(x: Int){
        
        let s = "value: \(x)"
        //self.message = s
        
    }
    
    var body: some View {
        TabView(selection: $selection){
            
            Text(self.message)
                .font(.title)
                .tabItem {
                    VStack {
                        Image("first")
                        Text("First")
                    }
            }
            .tag(0)

            Text("Second View")
                .font(.title)
                .tabItem {
                    VStack {
                        Image("second")
                        Text("Second")
                    }
                }
                .tag(1)
        }

        .onAppear{
            self.runTest()
            self.runMyTimer()
        }


    }
    
    private func runTest(){
        DispatchQueue.global(qos: .userInitiated).async {
            C_ThreadLoop()
            print("done")
        }
    }
    
    
    private func runMyTimer(){
        let timer = Timer.scheduledTimer(withTimeInterval: 1.0, repeats: true) { timer in
            self.message = buffer
        }
    }
}




struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}



///



@_cdecl("CallBackModule")
func swiftCallback(x: Int) -> Int {
    // swift process data...
    buffer = "C value: \(x)"
    return x + 2
    
}
