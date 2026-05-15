!pip install streamlit
!pip install opencv-python
!pip install Pillow
!pip install requests
!pip install numpy
!pip install pandas
!pip install plotly

# Additional dependencies for computer vision (if you want to extend later)
!pip install opencv-python-headless

# For deployment (optional)
!pip install streamlit-option-menu


import streamlit as st
import cv2
import numpy as np
from PIL import Image
import requests
import json
import time
import random
import hashlib
import base64
from datetime import datetime
import plotly.express as px
import plotly.graph_objects as go
import pandas as pd

# Configure Streamlit page
st.set_page_config(
    page_title="SecureShop AI",
    page_icon="🛡️",
    layout="wide",
    initial_sidebar_state="expanded"
)

# Custom CSS for better styling
st.markdown("""
<style>
    .main-header {
        background: linear-gradient(90deg, #1e3c72 0%, #2a5298 100%);
        padding: 1rem;
        border-radius: 10px;
        color: white;
        text-align: center;
        margin-bottom: 2rem;
    }
    .security-badge {
        background: #28a745;
        color: white;
        padding: 0.5rem 1rem;
        border-radius: 20px;
        font-weight: bold;
        display: inline-block;
        margin: 0.5rem;
    }
    .warning-badge {
        background: #ffc107;
        color: black;
        padding: 0.5rem 1rem;
        border-radius: 20px;
        font-weight: bold;
        display: inline-block;
        margin: 0.5rem;
    }
    .danger-badge {
        background: #dc3545;
        color: white;
        padding: 0.5rem 1rem;
        border-radius: 20px;
        font-weight: bold;
        display: inline-block;
        margin: 0.5rem;
    }
    .price-card {
        background: #f8f9fa;
        padding: 1rem;
        border-radius: 10px;
        border-left: 4px solid #007bff;
        margin: 1rem 0;
    }
    .privacy-score {
        font-size: 2rem;
        font-weight: bold;
        text-align: center;
        padding: 1rem;
        border-radius: 10px;
        margin: 1rem 0;
    }
</style>
""", unsafe_allow_html=True)

# Mock database of products with security features
PRODUCT_DATABASE = {
    "nike_air_max": {
        "name": "Nike Air Max 270",
        "brand": "Nike",
        "category": "Footwear",
        "authentic": True,
        "confidence": 0.94,
        "security_hash": "a1b2c3d4e5f6",
        "prices": {
            "Amazon": {"price": 130, "security_score": 85, "privacy_rating": "B+"},
            "Nike Official": {"price": 150, "security_score": 98, "privacy_rating": "A+"},
            "Footlocker": {"price": 135, "security_score": 78, "privacy_rating": "B"},
            "SuspiciousStore": {"price": 45, "security_score": 15, "privacy_rating": "F"}
        }
    },
    "iphone_14": {
        "name": "iPhone 14 Pro",
        "brand": "Apple",
        "category": "Electronics",
        "authentic": True,
        "confidence": 0.98,
        "security_hash": "x7y8z9w0v1u2",
        "prices": {
            "Apple Store": {"price": 999, "security_score": 100, "privacy_rating": "A+"},
            "Best Buy": {"price": 999, "security_score": 88, "privacy_rating": "A"},
            "Amazon": {"price": 979, "security_score": 85, "privacy_rating": "B+"},
            "CheapPhones": {"price": 299, "security_score": 25, "privacy_rating": "D"}
        }
    },
    "fake_rolex": {
        "name": "Rolex Submariner",
        "brand": "Rolex",
        "category": "Watches",
        "authentic": False,
        "confidence": 0.89,
        "security_hash": "INVALID",
        "prices": {
            "FakeWatches": {"price": 89, "security_score": 10, "privacy_rating": "F"},
            "AuthenticRolex": {"price": 8500, "security_score": 95, "privacy_rating": "A+"}
        }
    }
}

# Privacy protection simulator
def simulate_privacy_protection():
    """Simulate privacy protection features"""
    privacy_features = {
        "On-Device Processing": "✅ Enabled",
        "Data Encryption": "✅ AES-256",
        "Zero Data Storage": "✅ Active",
        "Secure Transmission": "✅ TLS 1.3",
        "Biometric Lock": "✅ Enabled"
    }
    return privacy_features

# Counterfeit detection simulator
def detect_counterfeit(product_data):
    """Simulate counterfeit detection"""
    if not product_data["authentic"]:
        return {
            "is_counterfeit": True,
            "confidence": product_data["confidence"],
            "warning": "⚠️ COUNTERFEIT DETECTED",
            "details": "Security hash validation failed. This product may be fake."
        }
    else:
        return {
            "is_counterfeit": False,
            "confidence": product_data["confidence"],
            "warning": "✅ AUTHENTIC PRODUCT",
            "details": "Security hash verified. This is a genuine product."
        }

# Security scoring for retailers
def calculate_retailer_security_score(retailer_data):
    """Calculate security score for retailers"""
    security_score = retailer_data["security_score"]
    privacy_rating = retailer_data["privacy_rating"]
    
    if security_score >= 90:
        return "🟢 SECURE", security_score, privacy_rating
    elif security_score >= 70:
        return "🟡 MODERATE", security_score, privacy_rating
    else:
        return "🔴 RISKY", security_score, privacy_rating

# Simulate product recognition
def recognize_product(image_data):
    """Simulate AI product recognition"""
    # Simulate processing time
    progress_bar = st.progress(0)
    for i in range(100):
        time.sleep(0.01)
        progress_bar.progress(i + 1)
    
    # Simulate recognition based on image characteristics
    products = list(PRODUCT_DATABASE.keys())
    recognized_product = random.choice(products)
    
    return PRODUCT_DATABASE[recognized_product]

# Main app header
st.markdown("""
<div class="main-header">
    <h1>🛡️ SecureShop AI</h1>
    <p>AI-Powered Shopping with Built-in Cybersecurity</p>
</div>
""", unsafe_allow_html=True)

# Sidebar for navigation
st.sidebar.title("🔧 Features")
demo_mode = st.sidebar.selectbox(
    "Choose Demo Mode:",
    ["📱 Product Scanner", "🔒 Privacy Dashboard", "⚠️ Security Analysis", "📊 Price Intelligence"]
)

if demo_mode == "📱 Product Scanner":
    st.header("📱 Smart Product Recognition")
    
    col1, col2 = st.columns([1, 1])
    
    with col1:
        st.subheader("📸 Upload Product Image")
        uploaded_file = st.file_uploader(
            "Take a photo or upload an image",
            type=['jpg', 'jpeg', 'png'],
            help="Upload an image of the product you want to analyze"
        )
        
        # Demo images
        st.subheader("🎯 Try Demo Images")
        demo_images = {
            "Nike Shoes": "demo_nike.jpg",
            "iPhone": "demo_iphone.jpg", 
            "Fake Rolex": "demo_rolex.jpg"
        }
        
        selected_demo = st.selectbox("Select a demo product:", list(demo_images.keys()))
        
        if st.button("🔍 Analyze Product", type="primary"):
            # Simulate the selected demo product
            if selected_demo == "Nike Shoes":
                product_data = PRODUCT_DATABASE["nike_air_max"]
            elif selected_demo == "iPhone":
                product_data = PRODUCT_DATABASE["iphone_14"]
            else:
                product_data = PRODUCT_DATABASE["fake_rolex"]
            
            # Store in session state
            st.session_state.current_product = product_data
    
    with col2:
        if 'current_product' in st.session_state:
            product_data = st.session_state.current_product
            
            st.subheader("🎯 Recognition Results")
            
            # Product Info
            st.success(f"**Identified**: {product_data['name']}")
            st.info(f"**Brand**: {product_data['brand']}")
            st.info(f"**Category**: {product_data['category']}")
            st.info(f"**Confidence**: {product_data['confidence']*100:.1f}%")
            
            # Authenticity Check
            counterfeit_result = detect_counterfeit(product_data)
            if counterfeit_result["is_counterfeit"]:
                st.error(counterfeit_result["warning"])
                st.error(counterfeit_result["details"])
            else:
                st.success(counterfeit_result["warning"])
                st.success(counterfeit_result["details"])
            
            # Security Hash
            if product_data["security_hash"] != "INVALID":
                st.success(f"🔐 Security Hash: {product_data['security_hash']}")
            else:
                st.error("❌ Security Hash: INVALID")

elif demo_mode == "🔒 Privacy Dashboard":
    st.header("🔒 Privacy Protection Dashboard")
    
    # Privacy features
    privacy_features = simulate_privacy_protection()
    
    col1, col2 = st.columns([1, 1])
    
    with col1:
        st.subheader("🛡️ Privacy Features")
        for feature, status in privacy_features.items():
            st.success(f"{feature}: {status}")
    
    with col2:
        st.subheader("📊 Privacy Score")
        privacy_score = 95
        
        # Privacy score gauge
        fig = go.Figure(go.Indicator(
            mode = "gauge+number",
            value = privacy_score,
            domain = {'x': [0, 1], 'y': [0, 1]},
            title = {'text': "Privacy Score"},
            gauge = {
                'axis': {'range': [None, 100]},
                'bar': {'color': "darkgreen"},
                'steps': [
                    {'range': [0, 50], 'color': "lightgray"},
                    {'range': [50, 80], 'color': "yellow"},
                    {'range': [80, 100], 'color': "lightgreen"}
                ],
                'threshold': {
                    'line': {'color': "red", 'width': 4},
                    'thickness': 0.75,
                    'value': 90
                }
            }
        ))
        fig.update_layout(height=300)
        st.plotly_chart(fig, use_container_width=True)
    
    # Data processing info
    st.subheader("📱 On-Device Processing")
    st.info("✅ All image processing happens on your device")
    st.info("✅ No personal data sent to external servers")
    st.info("✅ Shopping history encrypted locally")
    st.info("✅ Zero data retention policy")

elif demo_mode == "⚠️ Security Analysis":
    st.header("⚠️ Retailer Security Analysis")
    
    if 'current_product' not in st.session_state:
        st.warning("Please scan a product first to see security analysis")
        st.session_state.current_product = PRODUCT_DATABASE["nike_air_max"]
    
    product_data = st.session_state.current_product
    
    st.subheader(f"🔍 Security Analysis for: {product_data['name']}")
    
    # Create security analysis table
    security_data = []
    for retailer, data in product_data["prices"].items():
        security_status, score, privacy = calculate_retailer_security_score(data)
        security_data.append({
            "Retailer": retailer,
            "Security Status": security_status,
            "Security Score": score,
            "Privacy Rating": privacy,
            "Price": f"${data['price']}"
        })
    
    # Display security table
    df = pd.DataFrame(security_data)
    st.dataframe(df, use_container_width=True)
    
    # Security warnings
    st.subheader("⚠️ Security Warnings")
    for retailer, data in product_data["prices"].items():
        if data["security_score"] < 30:
            st.error(f"🚨 {retailer}: High risk - Poor security practices detected")
        elif data["security_score"] < 70:
            st.warning(f"⚠️ {retailer}: Moderate risk - Some security concerns")
        else:
            st.success(f"✅ {retailer}: Low risk - Good security practices")

elif demo_mode == "📊 Price Intelligence":
    st.header("📊 Smart Price Comparison")
    
    if 'current_product' not in st.session_state:
        st.warning("Please scan a product first to see price comparison")
        st.session_state.current_product = PRODUCT_DATABASE["nike_air_max"]
    
    product_data = st.session_state.current_product
    
    st.subheader(f"💰 Price Analysis for: {product_data['name']}")
    
    # Prepare price data
    price_data = []
    for retailer, data in product_data["prices"].items():
        price_data.append({
            "Retailer": retailer,
            "Price": data["price"],
            "Security Score": data["security_score"],
            "Privacy Rating": data["privacy_rating"]
        })
    
    df_prices = pd.DataFrame(price_data)
    
    # Price comparison chart
    fig = px.bar(
        df_prices, 
        x="Retailer", 
        y="Price",
        color="Security Score",
        title="Price vs Security Score",
        color_continuous_scale="RdYlGn"
    )
    st.plotly_chart(fig, use_container_width=True)
    
    # Price alerts
    st.subheader("💡 Smart Price Alerts")
    prices = [data["price"] for data in product_data["prices"].values()]
    avg_price = sum(prices) / len(prices)
    min_price = min(prices)
    max_price = max(prices)
    
    for retailer, data in product_data["prices"].items():
        price = data["price"]
        if price < avg_price * 0.5:  # Suspiciously low
            st.error(f"🚨 {retailer}: Price ${price} is suspiciously low (avg: ${avg_price:.0f}) - Possible counterfeit")
        elif price < min_price * 1.1:  # Best deal
            if data["security_score"] > 80:
                st.success(f"✅ {retailer}: Best secure deal at ${price}")
            else:
                st.warning(f"⚠️ {retailer}: Cheapest but security concerns")
        elif price > avg_price * 1.2:  # Overpriced
            st.info(f"💰 {retailer}: Premium pricing at ${price}")
    
    # Savings calculator
    st.subheader("💸 Savings Calculator")
    secure_retailers = {k: v for k, v in product_data["prices"].items() if v["security_score"] > 70}
    if secure_retailers:
        best_secure_price = min(secure_retailers.values(), key=lambda x: x["price"])
        worst_secure_price = max(secure_retailers.values(), key=lambda x: x["price"])
        savings = worst_secure_price["price"] - best_secure_price["price"]
        st.success(f"💰 Save ${savings} by choosing the most secure retailer!")

# Footer
st.markdown("---")
st.markdown("""
<div style="text-align: center; color: #666; padding: 2rem;">
    <p>🛡️ SecureShop AI - Protecting your shopping experience with AI and cybersecurity</p>
    <p>Built with ❤️ for the Retail Innovation Hackathon</p>
</div>
""", unsafe_allow_html=True)

# Add some demo instructions
with st.expander("📖 How to Use This Demo"):
    st.markdown("""
    **🎯 Demo Flow:**
    1. **Product Scanner**: Upload an image or try demo products
    2. **Privacy Dashboard**: See how your data is protected
    3. **Security Analysis**: Review retailer security scores  
    4. **Price Intelligence**: Compare prices with security insights
    
    **🔥 Key Features Demonstrated:**
    - AI product recognition with confidence scores
    - Counterfeit detection using security hashes
    - Retailer security scoring and privacy ratings
    - Price comparison with security warnings
    - On-device processing for privacy protection
    
    **🏆 Hackathon Winning Points:**
    - Combines AI with cybersecurity (2 topics!)
    - Solves real consumer problems
    - Scalable business model
    - Strong visual impact for demos
    """)