import UIKit
import MapKit
import CoreLocation
import CoreBluetooth

class glassesPeripheral: NSObject {
    public static let glassesLEDService     = CBUUID.init(string: "18424398-7CBC-11E9-8F9E-2A86E4085A59")
    public static let glassesLEDCharacteristicUUID   = CBUUID.init(string: "5A87B4EF-3BFA-76A8-E642-92933C31434F")
    public static let glassesLEDTimingCharacteristicUUID   = CBUUID.init(string: "BBF80E78-CE47-4CC5-9AFE-192215589DCD")
}

class ViewController: UIViewController, UISearchBarDelegate, MKMapViewDelegate, CBPeripheralDelegate, CBCentralManagerDelegate {

    @IBOutlet weak var directionLabel: UITextField!
    @IBOutlet weak var mapView: MKMapView!
    @IBOutlet weak var progressView: UIProgressView!
    @IBAction func centerButton(_ sender: Any, forEvent event: UIEvent) {
        mapView.userTrackingMode = .follow
    }
    @IBOutlet weak var glassesConnected: UIImageView!
    @IBOutlet weak var glassesConnectedLabel: UILabel!
    @IBOutlet weak var searchBar: UISearchBar!
    @IBOutlet weak var leftButtonOutlet: UIButton!
    @IBAction func leftButton(_ sender: Any) {
        if(leftSideConnected)
        {
            var valueToWrite:UInt8 = UInt8(10)
            writeLEDValueToChar(peripheralName: peripheral_left, withCharacteristic: ledTimeChar_Left!, withValue: Data([valueToWrite]))
            valueToWrite = 3
            writeLEDValueToChar(peripheralName: peripheral_left, withCharacteristic: ledChar_Left!, withValue: Data([valueToWrite]))
        }
    }
    @IBOutlet weak var rightButtonOutlet: UIButton!
    @IBAction func rightButton(_ sender: Any) {
        if(rightSideConnected)
        {
            var valueToWrite:UInt8 = UInt8(10)
            writeLEDValueToChar(peripheralName: peripheral_right, withCharacteristic: ledTimeChar_Right!, withValue: Data([valueToWrite]))
            valueToWrite = 3
            writeLEDValueToChar(peripheralName: peripheral_right, withCharacteristic: ledChar_Right!, withValue: Data([valueToWrite]))
        }
    }
    var locationManager = CLLocationManager()
    var currentCoordinate: CLLocationCoordinate2D!
    private var centralManager: CBCentralManager!
    private var peripheral_left: CBPeripheral!
    private var peripheral_right: CBPeripheral!
    private var ledChar_Left: CBCharacteristic?
    private var ledTimeChar_Left: CBCharacteristic?
    private var ledChar_Right: CBCharacteristic?
    private var ledTimeChar_Right: CBCharacteristic?
    var steps = [MKRoute.Step]()
    var stepCounter = 1
    var currentRegionIdentified = 0
    var distanceToRegionCenter = 0
    var isInRegionNumber = 0
    var totalNumberOfSteps = 0
    var destinationText = ""
    var distanceToRegionMax = 0
    var waitingForTurnsignal = false
    var primaryRoute: MKRoute?
    var leftSideConnected = false
    var rightSideConnected = false

    override func viewDidLoad() {
        super.viewDidLoad()
        centralManager = CBCentralManager(delegate: self, queue: nil)
        searchBar.delegate = self
        mapView.delegate = self
        locationManager.delegate = self
        locationManager.requestAlwaysAuthorization()
        locationManager.desiredAccuracy = kCLLocationAccuracyBestForNavigation
        locationManager.allowsBackgroundLocationUpdates = true
        locationManager.distanceFilter = kCLDistanceFilterNone
        //locationManager.activityType = .automotiveNavigation
        locationManager.startUpdatingLocation()
        self.locationManager.monitoredRegions.forEach({ self.locationManager.stopMonitoring(for: $0) })
        mapView.userTrackingMode = .follow
    }
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        print("DEBUG - Central state update")
        if central.state != .poweredOn {
            print("DEBUG - Central is not powered on")
        } else {
            print("DEBUG - Central scanning for glasses");
            centralManager.scanForPeripherals(withServices: [glassesPeripheral.glassesLEDService],
                                              options:nil)
        }
    }
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
            if let pname = peripheral.name {
                print("DEBUG - PERIPHERAL NAME \(pname)")
                if(leftSideConnected == false)
                {
                    if pname == "\u{25C0}\u{1F60E}" {
                        self.centralManager.stopScan()
                        self.peripheral_left = peripheral
                        self.peripheral_left.delegate = self
                        self.centralManager.connect(peripheral, options: nil)
                        print("DEBUG - Found \u{25C0}\u{1F60E}")
                    }
                }
                if(rightSideConnected == false)
                {
                    if pname == "\u{1F60E}\u{25B6}" {
                        self.centralManager.stopScan()
                        self.peripheral_right = peripheral
                        self.peripheral_right.delegate = self
                        self.centralManager.connect(peripheral, options: nil)
                        print("DEBUG - Found \u{1F60E}\u{25B6}")
                    }
                }
            }
        }
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        if peripheral == self.peripheral_left {
            print("DEBUG - Connected to the left side of your glasses")
            peripheral.discoverServices(nil);
            leftSideConnected = true
            leftButtonOutlet.tintColor = .systemPurple
            if(rightSideConnected)
            {
                glassesConnected.tintColor = .systemPurple
                glassesConnectedLabel.isHidden = false
            }
            else
            {
                centralManager.scanForPeripherals(withServices: nil, options:nil)
                glassesConnected.tintColor = .darkGray
                glassesConnectedLabel.isHidden = true
            }
        }
        if peripheral == self.peripheral_right {
            print("DEBUG - Connected to the right side of your glasses")
            peripheral.discoverServices(nil);
            rightSideConnected = true
            rightButtonOutlet.tintColor = .systemPurple
            if(leftSideConnected)
            {
                glassesConnected.tintColor = .systemPurple
                glassesConnectedLabel.isHidden = false
            }
            else
            {
                centralManager.scanForPeripherals(withServices: nil, options:nil)
                glassesConnected.tintColor = .darkGray
                glassesConnectedLabel.isHidden = true
            }
        }
    }
    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        if let services = peripheral.services {
            for service in services {
                print(service)
                if service.uuid == glassesPeripheral.glassesLEDService {
                    print("DEBUG - LED service found")
                    peripheral.discoverCharacteristics(nil, for: service)
                }
            }
        }
    }
    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        if peripheral == peripheral_left
        {
            if let characteristics = service.characteristics {
                for characteristic in characteristics {
                    print(characteristic)
                    if characteristic.uuid == glassesPeripheral.glassesLEDCharacteristicUUID {
                        print("DEBUG - LED characteristic found in left sided")
                        ledChar_Left = characteristic
                    }
                    if characteristic.uuid == glassesPeripheral.glassesLEDTimingCharacteristicUUID {
                        print("DEBUG - LED Timing characteristic found in left side")
                        ledTimeChar_Left = characteristic
                    }
                }
            }
        }
        if peripheral == peripheral_right
        {
            if let characteristics = service.characteristics {
                for characteristic in characteristics {
                    print(characteristic)
                    if characteristic.uuid == glassesPeripheral.glassesLEDCharacteristicUUID {
                        print("DEBUG - LED characteristic found in right side")
                        ledChar_Right = characteristic
                    }
                    if characteristic.uuid == glassesPeripheral.glassesLEDTimingCharacteristicUUID {
                        print("DEBUG - LED Timing characteristic found in right side")
                        ledTimeChar_Right = characteristic
                    }
                }
            }
        }
    }
    private func writeLEDValueToChar(peripheralName peripheral:CBPeripheral, withCharacteristic characteristic: CBCharacteristic, withValue value: Data) {
        peripheral.writeValue(value, for: characteristic, type: .withoutResponse)
    }
    private func writeLEDTimeValueToChar(peripheralName peripheral:CBPeripheral, withCharacteristic characteristic: CBCharacteristic, withValue value: Data) {
        peripheral.writeValue(value, for: characteristic, type: .withoutResponse)
    }
    
    func centralManager(_ central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: Error?) {
        if peripheral == self.peripheral_left {
            print("DEBUG - Disconnected from left side of glasses")
            self.peripheral_left = nil
            // Start scanning again
            print("DEBUG - Central scanning for glasses");
            centralManager.scanForPeripherals(withServices: nil,
                                              options:nil)
            glassesConnected.tintColor = .darkGray
            glassesConnectedLabel.isHidden = true
            leftButtonOutlet.tintColor = .darkGray
            leftSideConnected = false
        }
        if peripheral == self.peripheral_right {
            print("DEBUG - Disconnected from right side of glasses")
            self.peripheral_right = nil
            // Start scanning again
            print("DEBUG - Central scanning for glasses");
            centralManager.scanForPeripherals(withServices: nil,
                                              options:nil)
            glassesConnected.tintColor = .darkGray
            glassesConnectedLabel.isHidden = true
            rightButtonOutlet.tintColor = .darkGray
            rightSideConnected = false
        }
    }
    func getDirections(to destination: MKMapItem) {
        stepCounter = 1
        waitingForTurnsignal = false;
        let sourcePlacemark = MKPlacemark(coordinate: currentCoordinate)
        let sourceMapItem = MKMapItem(placemark: sourcePlacemark)

        let directionsRequest = MKDirections.Request()
        directionsRequest.source = sourceMapItem
        directionsRequest.destination = destination
        directionsRequest.transportType = .walking

        let directions = MKDirections(request: directionsRequest)
        directions.calculate { (response, _) in
            guard let response = response else { return }
//            guard let primaryRoute = response.routes.first else { return }
            self.primaryRoute = response.routes.first
            
            self.clearMap()
            self.mapView.addOverlay(self.primaryRoute!.polyline)
            self.steps = self.primaryRoute!.steps
            self.totalNumberOfSteps = self.primaryRoute!.steps.count-1
//            for i in 1 ..< primaryRoute.steps.count {
//                let step = primaryRoute.steps[i]
//                let region = CLCircularRegion(center: step.polyline.coordinate,
//                                              radius: 20,
//                                              identifier: "\(i)")
//                region.notifyOnEntry = true
//                self.locationManager.startMonitoring(for: region)
//                if i == (primaryRoute.steps.count-1)
//                {
//                    let circle = MKCircle(center: region.center, radius: region.radius)
//                    self.mapView.addOverlay(circle)
//                }
//            }
            //NEW STUFF
            var region = CLCircularRegion(center: self.primaryRoute!.steps[1].polyline.coordinate, radius: 20, identifier: "\(1)")
            region.notifyOnEntry = true
            self.locationManager.startMonitoring(for: region)
            
            region = CLCircularRegion(center: self.primaryRoute!.steps[self.totalNumberOfSteps].polyline.coordinate, radius: 20, identifier: "\(self.totalNumberOfSteps)")
            let circle = MKCircle(center: region.center, radius: region.radius)
            self.mapView.addOverlay(circle)
        }
    }
    func clearMap(){
        let overlays = self.mapView.overlays
        self.mapView.removeOverlays(overlays)
        self.locationManager.monitoredRegions.forEach({ self.locationManager.stopMonitoring(for: $0) })
        progressView.progress = 0;
        progressView.isHidden = true;
    }
    func mapView(_ mapView: MKMapView, rendererFor overlay: MKOverlay) -> MKOverlayRenderer {
        if overlay is MKPolyline {
            let renderer = MKPolylineRenderer(overlay: overlay)
            renderer.strokeColor = .systemPurple
            renderer.lineWidth = 5
            renderer.alpha = 1
            return renderer
        }
        if overlay is MKCircle {
            let renderer = MKCircleRenderer(overlay: overlay)
            renderer.strokeColor = .systemPurple
            renderer.lineWidth = 5
            renderer.fillColor = .white
            renderer.alpha = 1
            return renderer
        }
        return MKOverlayRenderer()
    }
    
    func searchBar(_ searchBar: UISearchBar, textDidChange searchText: String) {
    }
    
    func searchBarSearchButtonClicked(_ searchBar: UISearchBar) {
        print("DEBUG - \(searchBar.text ?? "EMPTY")")
        destinationText = searchBar.text!
        searchBar.text = ""
        searchBar.endEditing(true)
        
        searchAndMap(toDestination: destinationText)
    }
    func searchAndMap(toDestination: String) {
        let searchRequest = MKLocalSearch.Request()
        searchRequest.naturalLanguageQuery = toDestination

        let searchRegion = MKCoordinateRegion(center: currentCoordinate, span: MKCoordinateSpan(latitudeDelta: 0.1, longitudeDelta: 0.1))
        searchRequest.region = searchRegion
        
        let localSearch = MKLocalSearch(request: searchRequest)
        localSearch.start { (response, _) in
            guard let response = response else { return }
            guard let firstMapItem = response.mapItems.first else { return }
            
            self.getDirections(to: firstMapItem)
        }
    }
}

extension ViewController: CLLocationManagerDelegate {
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        guard let currentLocation = locations.first else { return }
        currentCoordinate = currentLocation.coordinate
        if(waitingForTurnsignal)
        {
            let nextLocation = CLLocation(latitude: steps[currentRegionIdentified].polyline.coordinate.latitude, longitude: steps[currentRegionIdentified].polyline.coordinate.longitude)
            let distanceToGo = nextLocation.distance(from: currentLocation)
            progressView.isHidden = false;
            progressView.progress = Float(Int(distanceToGo-25))/Float(75-25)
            print("DEBUG - New direction in: \(round(distanceToGo))m")
            if(distanceToGo <= 25)
            {
                if(currentRegionIdentified<totalNumberOfSteps)
                {
                    var region = CLCircularRegion(center: self.primaryRoute!.steps[currentRegionIdentified].polyline.coordinate, radius: 20, identifier: "\(currentRegionIdentified)")
                    self.locationManager.stopMonitoring(for: region)
                    region = CLCircularRegion(center: self.primaryRoute!.steps[currentRegionIdentified+1].polyline.coordinate, radius: 20, identifier: "\(currentRegionIdentified+1)")
                    region.notifyOnEntry = true
                    self.locationManager.startMonitoring(for: region)
                    print("DEBUG - Started monitoring region \(currentRegionIdentified+1)")
                    
                }
                progressView.progress = 0;
                progressView.isHidden = true;
                var valueToWrite:UInt8
                if steps[currentRegionIdentified].instructions.contains("left")
                {
                    if steps[currentRegionIdentified].instructions.contains("destination")
                    {
                        print("DEBUG - *GLASSES ALERT* Destination on left in \(round(distanceToGo))m")
                        if ledChar_Left != nil
                        {
                            valueToWrite = 10
                            writeLEDValueToChar(peripheralName: peripheral_left, withCharacteristic: ledTimeChar_Left!, withValue: Data([valueToWrite]))
                            valueToWrite = 2
                            writeLEDValueToChar(peripheralName: peripheral_left, withCharacteristic: ledChar_Left!, withValue: Data([valueToWrite]))
                        }
                    }
                    else
                    {
                        print("DEBUG - *GLASSES ALERT* Turn left in \(round(distanceToGo))m")
                        if ledChar_Left != nil
                        {
                            valueToWrite = 5
                            writeLEDValueToChar(peripheralName: peripheral_left, withCharacteristic: ledTimeChar_Left!, withValue: Data([valueToWrite]))
                            valueToWrite = 3
                            writeLEDValueToChar(peripheralName: peripheral_left, withCharacteristic: ledChar_Left!, withValue: Data([valueToWrite]))
                        }
                    }
                }
                if steps[currentRegionIdentified].instructions.contains("right")
                {
                    if steps[currentRegionIdentified].instructions.contains("destination")
                    {
                        print("DEBUG - *GLASSES ALERT* Destination on right in \(round(distanceToGo))m")
                        if ledChar_Right != nil
                        {
                            valueToWrite = 10
                            writeLEDValueToChar(peripheralName: peripheral_right, withCharacteristic: ledTimeChar_Right!, withValue: Data([valueToWrite]))
                            valueToWrite = 2
                            writeLEDValueToChar(peripheralName: peripheral_right, withCharacteristic: ledChar_Right!, withValue: Data([valueToWrite]))
                        }
                    }
                    else
                    {
                        print("DEBUG - *GLASSES ALERT* Turn right in \(round(distanceToGo))m")
                        if ledChar_Right != nil
                        {
                            valueToWrite = 5
                            writeLEDValueToChar(peripheralName: peripheral_right, withCharacteristic: ledTimeChar_Right!, withValue: Data([valueToWrite]))
                            valueToWrite = 3
                            writeLEDValueToChar(peripheralName: peripheral_right, withCharacteristic: ledChar_Right!, withValue: Data([valueToWrite]))
                        }
                    }
                }
                if currentRegionIdentified >= totalNumberOfSteps
                {
                    print("DEBUG - Destination reached!")
                    clearMap()
                }
                waitingForTurnsignal = false;
            }
        }
    }
    func locationManager(_ manager: CLLocationManager, didDetermineState state: CLRegionState, for region: CLRegion) {
        switch state {
        case .inside:
            waitingForTurnsignal = true
            currentRegionIdentified = Int(region.identifier)!
            let nextLocation = CLLocation(latitude: steps[currentRegionIdentified].polyline.coordinate.latitude, longitude: steps[currentRegionIdentified].polyline.coordinate.longitude)
            let currentLocation = CLLocation(latitude: currentCoordinate.latitude, longitude: currentCoordinate.longitude)
            let distanceToGo = nextLocation.distance(from: currentLocation)
            distanceToRegionMax = Int(distanceToGo)
            break
        case .outside:
            break
        default:
            break
        }
    }

}
